<?php
include("db-connection.php");

function fetchCar($con, $carId) {
    $sql = "SELECT * FROM cars WHERE id=?";
    $stmt = mysqli_prepare($con, $sql);
    mysqli_stmt_bind_param($stmt, "i", $carId);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);
    
    $carData = mysqli_fetch_assoc($result);
    
    // Send response as json
    header("Content-Type: application/json");
    echo json_encode($carData);
    
    mysqli_stmt_close($stmt);
    mysqli_close($con);
}

// If car ID is provided in the url
if(isset($_GET['id'])) {
    $carId = $_GET['id'];
    fetchCar($con, $carId);
} else {
    echo "Car ID not provided.";
}
?>
