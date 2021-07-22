const express = require("express");
const app = express();

app.use(express.json());

var data = "IoT Temperature and Humidity data sensor";

app.get('/',(req,res)=>{
    res.send(data);
})


app.post('/',(request,respond) => {
    var text = request.body.data;
    
    data = `<h1>The data is : ${text} </h1>`
    console.log(text)
    respond.sendStatus(200);
});

app.listen(5000,(req,res) => {
    console.log("start at port 5000");
})