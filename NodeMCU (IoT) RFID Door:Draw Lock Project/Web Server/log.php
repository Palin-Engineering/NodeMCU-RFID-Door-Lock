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
 
 
    if(!empty($_POST['tag']) && !empty($_POST['area']))
    {
        $tag = $_POST['tag'];
        $area = $_POST['area'];
        
        $sql = "INSERT INTO logs (tag, area)
        
        VALUES ('$tag', '$area')";
 
        if ($conn->query($sql) === TRUE) {
            echo "LOGGED OK" .$sql;
        } else {
            echo "LOGGED Error: " . $sql . "<br>" . $conn->error;
        }
    }
 
 
    $conn->close();
?>