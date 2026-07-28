let express = require('express');
let cors = require('cors');

let app = express();
let puerto = process.env.PORT || 3000;

app.use(cors());
app.use(express.json());

let datos_esp32 = {
    temperatura: 0,
    humedad_suelo: 0,
    humedad: 0,
    ph: 0,
    ventilador: false,
    ultima_actualizacion: null
};

app.get("/api/datos", (req, res) => {
    res.json(datos_esp32);
});

app.post("/api/datos", (req, res) => {
    datos_esp32 = { ...req.body, ultima_actualizacion: Date.now() };
    console.log(datos_esp32);
    res.sendStatus(200);
});

app.listen(puerto, () => {
    console.log("Servidor corriendo en el puerto: " + puerto);
});