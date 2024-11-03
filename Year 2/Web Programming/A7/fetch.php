<?php
include("db-connection.php");

function fetchData($con){
    $sql = "SELECT * FROM cars";
    $result = mysqli_query($con, $sql);

    $response = array();
    if ($result && mysqli_num_rows($result) > 0) {
        while ($row = mysqli_fetch_assoc($result)) {
            $response[] = $row;
        }
    }
    // Send response as json
    header("Content-Type: application/json");
    echo json_encode($response);
    // // Close database connection
    mysqli_close($con);
}
// Data retrieval
fetchData($con);
