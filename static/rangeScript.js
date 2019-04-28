function addNewPlayer(language) {
    var players = document.getElementById("players");
    var p = parseInt(players.value);

    var table = document.getElementById("inputTable");
    var newRow = table.insertRow(3+p);
    p += 1;
    var cell1 = newRow.insertCell(0);
    cell1.class = "inputHeader";
    if (language == 'chinese') {
        cell1.innerHTML = "玩家 " + p.toString();
    } else {
        cell1.innerHTML = "Player " + p.toString();
    }
    var cell2 = newRow.insertCell(1);
    cell2.innerHTML = "<input name=\"p"+p.toString()+"\">";

    players.value = p;
    var display = document.getElementById("playersDisplay");
    if (language == 'chinese'){
        display.innerHTML = "玩家: " + p.toString();
    } else {
        display.innerHTML = "Players: " + p.toString();
    }
    if (p == 6){
        var button = document.getElementById("addPlayer");
        button.disabled = true;
    }
    var button = document.getElementById("remPlayer");
    button.disabled = false;
}

function removePlayer(language) {
    var players = document.getElementById("players");
    var p = parseInt(players.value);

    var table = document.getElementById("inputTable");
    var newRow = table.deleteRow(2+p);
    p -= 1;
    players.value = p;
    var display = document.getElementById("playersDisplay");
    if (language == 'chinese'){
        display.innerHTML = "玩家: " + p.toString();
    } else {
        display.innerHTML = "Players: " + p.toString();
    }
    if (p == 2){
        var button = document.getElementById("remPlayer");
        button.disabled = true;
    }
    var button = document.getElementById("addPlayer");
    button.disabled = false;
}