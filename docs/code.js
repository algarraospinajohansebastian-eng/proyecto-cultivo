const BACKEND_URL = "https://TU-BACKEND.onrender.com"; // <- lo cambias en el paso 4, cuando tengas la URL real de Render

let temperatura_mostrar = document.getElementById("temperatura");
let humedad_mostrar = document.getElementById("humedad");
let humedad_suelo_mostrar = document.getElementById("humedad_suelo");
let ph_mostrar = document.getElementById("ph");
let ventilador_mostrar = document.getElementById("ventilador");

async function actualizar(){
    let datos;
    try{
        let datos_recibidos = await fetch(BACKEND_URL + "/api/datos");
        datos = await datos_recibidos.json();
    }
    catch(err){
        console.log("hubo un error bro " + err);
        return;
    }

    let ventilador_bool = datos.ventilador ? "Encendido" : "Apagado";

    temperatura_mostrar.innerHTML = "Temperatura: " + datos.temperatura + "°C";
    humedad_mostrar.innerHTML = "Humedad: " + datos.humedad + "%";
    humedad_suelo_mostrar.innerHTML = "Humedad del suelo: " + datos.humedad_suelo + "%";
    ph_mostrar.innerHTML = "pH: " + datos.ph;
    ventilador_mostrar.innerHTML = "Estado ventilador: " + ventilador_bool;
}

actualizar();
setInterval(actualizar, 1000);