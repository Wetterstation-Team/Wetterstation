#ifndef WEBPAGE_H
#define WEBPAGE_H

char* website = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Wetterstation Controller</title>
  <link rel="icon" href="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn-icons-png.flaticon.com%2F512%2F4432%2F4432329.png&f=1&nofb=1&ipt=943430f4594490582558e7892c5dc155601cb9dee82573f64b3f4375003efdde" type="image/x-icon">
  <link rel="icon" href="data:,">
  <style>
    html {
      font-family: Helvetica;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
    .button {
      background-color: #4CAF50;
      border: none;
      color: white;
      padding: 16px 40px;
      text-decoration: none;
      font-size: 30px;
      margin: 2px;
      cursor: pointer;
    }
    .button2 {
      background-color: #555555;
    }
  </style>


  <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js"></script>
  <script defer>
  let tempValues = [];
  let humValues = [];
  let chartInstance;

  async function fetchData(endpoint, updateFunc) {
    try {
      const response = await fetch(endpoint);
      if (!response.ok) throw new Error(`HTTP error! Status: ${response.status}`);
      const data = await response.text();
      updateFunc(data);
    } catch (err) {
      console.error(`Error fetching data from ${endpoint}:`, err);
    }
  }

  function updateTemp(data) {
    document.getElementById("temp").innerHTML = data;
    tempValues.push(Number(data));
    if (tempValues.length > 30) {
      tempValues.shift();
    }
  }

  function updateHum(data) {
    document.getElementById("hum").innerHTML = data;
    humValues.push(Number(data));
    if (humValues.length > 30) {
      humValues.shift();
    }
  }

  async function updateData() {
    while (true) {
      await fetchData('/temp', updateTemp);
      await fetchData('/hum', updateHum);

      chartInstance.data.datasets[0].data = tempValues;
      chartInstance.data.datasets[1].data = humValues;
      chartInstance.update();

      await new Promise(resolve => setTimeout(resolve, 10000));
    }
  }

  document.addEventListener("DOMContentLoaded", () => {
    const xValues = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];
    chartInstance = new Chart("graph", {
      type: "line",
      data: {
        labels: xValues,
        datasets: [{
          label: "Temperature",
          data: tempValues,
          borderColor: "red",
          fill: false
        },{
          label: "Humidity",
          data: humValues,
          borderColor: "green",
          fill: false
        }]
      },
      options: {
        legend: {display: true}
      }
    });
    updateData();
  });
</script>


</head>
<body>
  <div>
    <h1>Wetter Control v1.2</h1>
    <a href="/on"><button class="button">ON</button></a>
    <a href="/off"><button class="button button2">OFF</button></a>
    <p>Temperature: </p><p id="temp"></p><p>Humidity: </p><p id="hum"></p>
  </div>
  <div style="position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); width: 800px;">
    <canvas id="graph" style="width: 100%;max-width:1000px"></canvas>
  </div>
</body>
</html>
)=====";
#endif