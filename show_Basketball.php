<?php
    $rounte1 = 0;
    include("./connectDB.php");



?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Basketball</title>
</head>
<style>
@import url('https://fonts.googleapis.com/css2?family=Mitr:wght@200&display=swap');
body {
  background-color: rgb(238,232,170);
}

h1.a {
  color: rgb(0, 0, 0);
  text-align: center;
  font-size: 55px;
  font-family: 'Mitr', sans-serif;
}
table.one {
    background-color: rgb(233,150,122);
    color: rgb(0,0,0);
    font-size: 40px;
    font-family: 'Mitr', sans-serif;

    }
table.two {
    background-color: rgb(233,150,122);
    color: rgb(0,0,0);
    font-size: 15px;
    font-family: 'Mitr', sans-serif;

    }
th ,td {
    border:3px solid black;
    
    }

</style>
<body>
            <h1 class="a" align = "center">Basketball</h1>&nbsp;
<?php

    $sql = "SELECT redscore, bluescore FROM score_data WHERE gameEnd = '1' AND sport = 'basketball' ";

    $result = $conn->query($sql);

    if ($result->num_rows > 0) { 

// output data of each row
    echo "<table class= 'one' border='1' align = 'center' ><th>GAME</th><th>RED SCORE</th><th>BLUE SCORE</th>";

    while($row = $result->fetch_assoc()) {
        $rounte1++ ;
    echo "<tr>";
    echo "<td>".$rounte1."</td>";
    echo "<td>".$row['redscore']."</td>";
    echo "<td>".$row['bluescore']."</td>";
    echo "</tr>";
    }
    echo "</table>&nbsp";
}   else {
    echo "0 results";
    }



?>

 <div class="container" align= "center">
<table class="two" >
        <thead>
                <tr>

                    <th text-align="center">Sport</th>
                    <th text-align="center">GameNum</th>
                    <th text-align="center">Redscore</th>
                    <th text-align="center">Bluescore</th>
                    <th text-align="center">Balltime</th>
                    <th text-align="center">Quarter</th>
                    <th text-align="center">Day</th>
                    <th text-align="center">GameEnd</th>


                </tr>
        </thead>

    <tbody>
<?php
    include("./connectDB.php");

    $query = "SELECT * FROM score_data WHERE sport = 'basketball' LIMIT 10";
    $result = mysqli_query($conn, $query);

    foreach($result as $row) { ?>
    <tr>

                <td> <?php echo $row['sport']; ?></td>
                <td> <?php echo $row['gameNum']; ?></td>
                <td> <?php echo $row['redscore']; ?></td>
                <td> <?php echo $row['bluescore']; ?></td>
                <td> <?php echo $row['ballTime']; ?></td>
                <td> <?php echo $row['quarter']; ?></td>
                <td> <?php echo $row['day']; ?></td>
                <td> <?php echo $row['gameEnd']; ?></td>

    </tr>

<?php } ?>
</tbody>
</table>
</div>


</body>
</html>