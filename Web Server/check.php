<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "";
    $password = "";
    $dbname = "";
 
    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }
 
    //Get current date and time
    date_default_timezone_set('Europe/London');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");
 
    if(!empty($_POST['tag']) && !empty($_POST['area']))
    {
        $tag = $_POST['tag'];
        $area = $_POST['area'];
 
        $sql = "SELECT * FROM Profile WHERE level = '$area' AND tag = '$tag'";

        $res = mysqli_query($conn, $sql);

        $row = mysqli_fetch_array($res);

 
        if ($conn->query($sql)->num_rows > 0) {
            echo $row['name'];
            
        } else {
            echo "0";
        }
    }
 
 
    $conn->close();
?>