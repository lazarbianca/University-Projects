<?php
include("db-connection.php");

$model = $_POST['model'];
$enginePower = $_POST['enginePower'];
$fuel = $_POST['fuel'];
$price = $_POST['price'];
$color = $_POST['color'];
$age = $_POST['age'];
$history = $_POST['history'];

// Prepare the INSERT query
$sql = "INSERT INTO cars (model, engine_power, fuel, price, color, age, history)
        VALUES (?, ?, ?, ?, ?, ?, ?)";

$stmt = mysqli_prepare($con, $sql);
mysqli_stmt_bind_param($stmt, "sisisis", $model, $enginePower, $fuel, $price, $color, $age, $history);

if (mysqli_stmt_execute($stmt)) {
    echo "Car added successfully!";
} else {
    echo "Error: " . mysqli_error($stmt);
}

mysqli_stmt_close($stmt);
mysqli_close($con);
?>