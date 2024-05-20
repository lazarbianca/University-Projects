<?php
include("db-connection.php");

// Ensure the 'id' parameter is set and is an integer
$id = isset($_POST['id']) ? intval($_POST['id']) : null;

$response = array();

if ($id !== null) {
    // Prepare the DELETE query
    $sql = "DELETE FROM cars WHERE id=?";

    $stmt = mysqli_prepare($con, $sql);
    
    if ($stmt) {
        // Bind parameters
        mysqli_stmt_bind_param($stmt, "i", $id);
        
        // Execute the statement
        if (mysqli_stmt_execute($stmt)) {
            $response['message'] = "Car deleted successfully!";
        } else {
            $response['error'] = "Error: " . mysqli_stmt_error($stmt);
        }

        // Close the statement
        mysqli_stmt_close($stmt);
    } else {
        $response['error'] = "Error preparing statement: " . mysqli_error($con);
    }
} else {
    $response['error'] = "Invalid or missing 'id' parameter.";
}

// Send response as JSON
header("Content-Type: application/json");
echo json_encode($response);

// Close the connection
mysqli_close($con);