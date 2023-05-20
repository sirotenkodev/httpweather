if (localStorage.getItem("city") === null) {
    localStorage.setItem('city', "Omsk");
}

window.addEventListener('load', async (event) => {
    let response = await fetch("/getjsondata?city=" + localStorage.getItem('city'));
    if (response.ok) {
        let json = await response.json();
        document.getElementById("imgdata").src="//openweathermap.org/themes/openweathermap/assets/vendor/owm/img/widgets/" + json.imgdata + ".png";
        document.getElementById("tempdata").innerText=json.tempdata + "°C";
        document.getElementById("descriptiondata").innerText=json.descriptiondata;
        document.getElementById("citydata").innerText=json.citydata;
    } else {
        alert("Ошибка HTTP: " + response.status);
    }
});

let form = document.getElementById('formdata');

form.addEventListener("submit", async (e) => {
    e.preventDefault();
    
    localStorage.setItem('city', document.getElementById("city-name").value);
    let response = await fetch("/getjsondata?city=" + localStorage.getItem('city'));

    if (response.ok) {
        let json = await response.json();
        document.getElementById("imgdata").src="//openweathermap.org/themes/openweathermap/assets/vendor/owm/img/widgets/" + json.imgdata + ".png";
        document.getElementById("tempdata").innerText=json.tempdata + "°C";
        document.getElementById("descriptiondata").innerText=json.descriptiondata;
        document.getElementById("citydata").innerText=json.citydata;
    } else {
        alert("Ошибка HTTP: " + response.status);
    }
  });