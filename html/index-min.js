null===localStorage.getItem("city")&&localStorage.setItem("city","Omsk"),window.addEventListener("load",(async t=>{let e=await fetch("/getjsondata?city="+localStorage.getItem("city"));if(e.ok){let t=await e.json();document.getElementById("imgdata").src="//openweathermap.org/themes/openweathermap/assets/vendor/owm/img/widgets/"+t.imgdata+".png",document.getElementById("tempdata").innerText=t.tempdata+"°C",document.getElementById("descriptiondata").innerText=t.descriptiondata,document.getElementById("citydata").innerText=t.citydata}else alert("Ошибка HTTP: "+e.status)}));let form=document.getElementById("formdata");form.addEventListener("submit",(async t=>{t.preventDefault(),localStorage.setItem("city",document.getElementById("city-name").value);let e=await fetch("/getjsondata?city="+localStorage.getItem("city"));if(e.ok){let t=await e.json();document.getElementById("imgdata").src="//openweathermap.org/themes/openweathermap/assets/vendor/owm/img/widgets/"+t.imgdata+".png",document.getElementById("tempdata").innerText=t.tempdata+"°C",document.getElementById("descriptiondata").innerText=t.descriptiondata,document.getElementById("citydata").innerText=t.citydata}else alert("Ошибка HTTP: "+e.status)}));