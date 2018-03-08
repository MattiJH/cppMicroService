var ip = "192.168.137.1:6502"

function getFormData(){
    console.log("Collecting ID");
    var song_id = document.getElementById("song_id").value;
    console.log("Collected ID");
    song_id = parseInt(song_id);
    if(isNaN(song_id)){
        song_id = -1;
    }
    console.log("song_id: "+song_id);
    var song_name = document.getElementById("song_name").value;
    console.log("song_name: "+song_name);
    var artist = document.getElementById("artist").value;
    console.log("artist: "+artist);
    var album = document.getElementById("album").value;
    console.log("album: "+album);
    var lenght = document.getElementById("lenght").value;
    console.log("lenght: "+lenght);
    var year = document.getElementById("year").value;
    console.log("year: "+year);
    var lyrics = document.getElementById("lyrics").value;
 
    lyrics = lyrics.replace(/\r?\n/g, ' ');
    lyrics = lyrics.replace(/["]/g, ' ');
    console.log("lyrics: "+lyrics);

    if(!typeof song_id == "number"){
        window.alert("Error: id not a number");
        return null;
    }else{
       var jsonAsText = "{"+
        '"song_name" : "'+ song_name +'",'+
        '"artist": "'+ artist+'",'+
        '"album": "'+ album+'",'+
        '"song_id":'+ song_id+','+
        '"lenght": "'+ lenght+'",'+
        '"lyrics": "'+ lyrics+'",'+
        '"year": "'+ year+'"}';
        return jsonAsText;
    }
}
function update(){
    console.log("updating")
    
    var jsonAsText = getFormData()
    if(jsonAsText != null){
        console.log(jsonAsText)

        var xmlhttp = new XMLHttpRequest();
        var url = "http://"+ip+"/api/songs/update";
    
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
        var json = JSON.parse(jsonAsText);
        delete json.lyrics;
        jsonAsText = JSON.stringify(json);

        var xmlhttp = new XMLHttpRequest();
        var url = "http://"+ip+"/api/songs/delete";
    
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
        var url = "http://"+ip+"/api/songs/add";
    
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
    var url = "http://"+ip+"/api/songs/search";
   
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
    var url = "http://"+ip+"/api/songs/all";
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
    var out = "<table>"+
    "<tr>"+
    "<th>Song id</th>"+
    "<th>Song Name</th>"+
    "<th>Artist</th>"+
    "<th>Album</th>"+
    "<th>Length</th>"+
    "<th>Year</th>"+
    "<th>Lyrics</th>"+
    "</tr>";
    if(arr != null){
  
    var i;
    console.log(arr);
    for(i = 0; i < arr.length; i++) {
        out += "<tr>"+
        "<td>"+ arr[i].song_id +"</td>"+
        "<td>"+arr[i].song_name+"</td>"+
        "<td>"+arr[i].artist +"</td>"+
        "<td>"+arr[i].album+"</td>"+
        "<td>"+arr[i].lenght+"</td>"+
        "<td>"+arr[i].year+"</td>"+
        "<td>"+arr[i].lyrics+"</td>"+
        "</tr>"
    }
    out += "</table>"
    document.getElementById("restResults").innerHTML = out;
    }else{
        out += "</table>"
        document.getElementById("restResults").innerHTML = out
    }
}