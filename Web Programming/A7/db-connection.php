<?php
// Database credentials
$host = 'localhost';
$dbname = 'car_management';
$username = 'root';
$password = '';

// Attempt to connect to the database
$con = connectToDatabase($host, $dbname, $username, $password);
function connectToDatabase($host, $dbname, $username, $password) {
    $con = mysqli_connect($host, $username, $password, $dbname);
    // Check connection
    if (!$con) {
        die("Connection failed: " . mysqli_connect_error());
    }
    return $con;
}
