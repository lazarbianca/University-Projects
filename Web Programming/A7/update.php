<?php
include("db-connection.php");

$id = $_POST['id'];
$model = $_POST['model'];
$enginePower = $_POST['enginePower'];
$fuel = $_POST['fuel'];
$price = $_POST['price'];
$color = $_POST['color'];
$age = $_POST['age'];
$history = $_POST['history'];

// Prepare the UPDATE query
$sql = "UPDATE cars 
        SET model=?, engine_power=?, fuel=?, price=?, color=?, age=?, history=?
        WHERE id=?";

$stmt = mysqli_prepare($con, $sql);
mysqli_stmt_bind_param($stmt, "sisisisi", $model, $enginePower, $fuel, $price, $color, $age, $history, $id);

$response = array();
if (mysqli_stmt_execute($stmt)) {
    $response['message'] = "Car updated successfully!";
} else {
    $response['error'] = "Error: " . mysqli_stmt_error($stmt);
}

// Send response as json
header("Content-Type: application/json");
echo json_encode($response);

mysqli_stmt_close($stmt);
mysqli_close($con);
?>
