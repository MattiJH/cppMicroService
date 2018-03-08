var ip = "192.168.137.1:6502"

function getFormData(){
    var id = document.getElementById("Location_id").value
    id = parseInt(id)
    if(isNaN(id)){
        id = -1
    }
    console.log("id: "+id)
    var name = document.getElementById("Location_name").value
    console.log("name: "+name)
    var address = document.getElementById("Location_address").value
    console.log("address: "+address)
    var city = document.getElementById("Location_city").value
    console.log("city: "+city)
    var zip = document.getElementById("Location_zip").value
    zip = parseInt(zip)
    if(isNaN(zip)){
        zip = -1
    }
    console.log("zip: "+zip)
    var country = document.getElementById("Location_country").value
    console.log("country: "+country)

    if(!(typeof id == "number" && typeof zip == "number")){
        window.alert("Error: id/zip not a number")
        return null
    }else{
       var jsonAsText = "{"+
        '"Location_address" : "'+ address +'",'+
        '"Location_city": "'+ city+'",'+
        '"Location_country": "'+ country+'",'+
        '"Location_id":'+ id+','+
        '"Location_name": "'+ name+'",'+
        '"Location_zip":'+ zip +"}"
        return jsonAsText
    }
}
function update(){
    console.log("updating")
    
    var jsonAsText = getFormData()
    if(jsonAsText != null){
        console.log(jsonAsText)

        var xmlhttp = new XMLHttpRequest();
        var url = "http://"+ip+"/api/locations/update";
    
        xmlhttp.open("POST", url, false); 
        xmlhttp.setRequestHeader("Content-Type", "application/json");
        
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                formatResponseMessage(response);
            }
        }
        xmlhttp.send(jsonAsText);
    }
 }

function deleteData(){
    console.log("Deleting")

    var jsonAsText = getFormData();
    if(jsonAsText != null){

        console.log(jsonAsText);

        var xmlhttp = new XMLHttpRequest();
        var url = "http://"+ip+"/api/locations/delete";
    
        xmlhttp.open("DELETE", url, false); 
        xmlhttp.setRequestHeader("Content-Type", "application/json");
        
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                formatResponseMessage(response);
            }
        }
        xmlhttp.send(jsonAsText);
    }    

   
}
function insert(){

    console.log("Inserting")
    
    var jsonAsText = getFormData()
    if(jsonAsText != null){
        console.log(jsonAsText);
        var json = JSON.parse(jsonAsText);
        delete json.id;
        jsonAsText = JSON.stringify(json);
        var xmlhttp = new XMLHttpRequest();
        var url = "http://"+ip+"/api/locations/add";
    
        xmlhttp.open("POST", url, false); 
        xmlhttp.setRequestHeader("Content-Type", "application/json");
        
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                formatResponseMessage(response);
            }
        }
        xmlhttp.send(jsonAsText);
    }
}
function search(){
    console.log("Searching")
   var jsonAsText = getFormData();
    if(jsonAsText != null){
       console.log(jsonAsText)
 
    var xmlhttp = new XMLHttpRequest();
    var url = "http://"+ip+"/api/locations/search";
   
    xmlhttp.open("POST", url, false); 
    xmlhttp.setRequestHeader("Content-Type", "application/json");
    
    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            var response = JSON.parse(xmlhttp.responseText);
            formatResponse(response);
        }
    }
    xmlhttp.send(jsonAsText);
    }
   
}

function getAll(){
    var xmlhttp = new XMLHttpRequest();
    var url = "http://"+ip+"/api/locations/all";
    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            var response = JSON.parse(xmlhttp.responseText);
            formatResponse(response);
        }
    }
    xmlhttp.open("GET", url, true); 
    xmlhttp.send();
}

function formatResponseMessage(arr){
    console.log(arr)
    var out = "<p>"+arr.Results+"</p>"
    document.getElementById("restMessage").innerHTML = out;
}


function formatResponse(arr) {
    var out = "<table><tr><th>ID</th><th>Name</th><th>Address</th><th>City</th><th>Zip</th><th>Country</th></tr>";
    var i;
    for(i = 0; i < arr.length; i++) {
        out += "<tr><th>"+ arr[i].Location_id +"</th><th>"+arr[i].Location_name
        +"</th><th>"+arr[i].Location_address +"</th><th>"+arr[i].Location_city
        +"</th><th>"+arr[i].Location_zip+"</th><th>"+arr[i].Location_country+"</th></tr>"
    }
    out += "</table>"
    document.getElementById("restResults").innerHTML = out;
}