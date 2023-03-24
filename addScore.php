<?php
//$temp=$_GET['temp'];              //ค่าที่ GET มาจาก Arduino
//$humidity=$_GET['humidity'];      //ค่าที่ GET มาจาก Arduino

date_default_timezone_set("Asia/Bangkok");

$sport=$_POST['sport'];
$redscore=$_POST['redscore'];
$bluescore=$_POST['bluescore'];
$ballTime=$_POST['ballTime'];
$quarter=$_POST['quarter'];
$endSport=$_POST['endSport'];


$servername = "192.168.235.157";
$username = "root";
$password = "";
$database = "scoreboard_project";
$conn = mysqli_connect($servername, $username, $password, $database);

$sql = "SELECT * FROM score_data ORDER BY ID DESC LIMIT 1;";
$query = mysqli_query($conn,$sql);
$data = mysqli_fetch_assoc($query);

$Game = $data['gameNum'];
$gameEnd = $data['gameEnd'];



//CHECK CONNECTION
if($conn->connect_error)
{
    die("Connection failed : ".$conn->connect_error);
}

//CHECK NEWGAME
if($gameEnd == 1)
{
    $Game = $Game + 1;
    $gameEnd = 0;  
}  

if($endSport == 1)
{
    $gameEnd = 1;
} 

//CHECK SPORT
if($sport == 0)
{
    $sport = "Basketball";
    $ballTime = null;
}

if($sport == 1)
{
    $sport = "Football";
    $quarter = null;
    if($ballTime == 0){$ballTime = "Frist-haft";}
    else{$ballTime = "Second-half";}
}
//SQL
$sqli="INSERT INTO score_data(gameNum,sport,redscore,bluescore,ballTime,quarter,day,gameEnd) VALUES('$Game','$sport','$redscore','$bluescore','$ballTime','$quarter',CURRENT_TIMESTAMP,'$gameEnd')";

$sql = "SELECT MAX(gameNum) as gameNum FROM score_data;";
$query = mysqli_query($conn,$sql);
$data = mysqli_fetch_assoc($query);
$Game = $data['gameNum'];



if ($conn->query($sqli)===true) { echo "[SAVE]";} 
else {echo "Error : ".$sqli ."<br>".$conn->error;}
$conn->close();
?>