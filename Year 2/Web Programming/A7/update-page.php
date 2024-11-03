<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Update Car Details</title>
  </head>
  <body>
    <h1>Update Car</h1>
    <a href="index.html">Back</a>
    
    <form id="updateCarForm">
      <input
        type="hidden"
        id="id"
        name="id"
        value="<?php echo htmlspecialchars($_GET['id']); ?>"
      />

      <label for="model">Model:</label>
      <input type="text" id="model" name="model" required /><br />

      <label for="enginePower">Engine Power:</label>
      <input type="number" id="enginePower" name="enginePower" required /><br />

      <label for="fuel">Fuel:</label>
      <input type="text" id="fuel" name="fuel" required /><br />

      <label for="price">Price:</label>
      <input type="number" id="price" name="price" required /><br />

      <label for="color">Color:</label>
      <input type="text" id="color" name="color" required /><br />

      <label for="age">Age:</label>
      <input type="number" id="age" name="age" required /><br />

      <label for="history">History:</label>
      <input type="text" id="history" name="history" /><br />

      <button type="submit">Update Car</button>
    </form>

    <div id="message"></div>

    <script src="./jquery-3.7.1.js"></script>
    <script>
      $(document).ready(function () {
        // Fetch car details
        const carId = $("#id").val();
        $.ajax({
          type: "GET",
          url: "fetch-one.php?id=" + carId, // Using fetch-one
          dataType: "json",
          success: function (data) {
            // Populate form fields with car details
            $("#model").val(data.model);
            $("#enginePower").val(data.engine_power);
            $("#fuel").val(data.fuel);
            $("#price").val(data.price);
            $("#color").val(data.color);
            $("#age").val(data.age);
            $("#history").val(data.history);
          },
          error: function () {
            $("#message").text("Error fetching car details.");
          },
        });

        // Handle form submission
        $("#updateCarForm").submit(function (e) {
          e.preventDefault(); // Prevent form submission

          // Gather data that the user updated
          const id = $("#id").val();
          const model = $("#model").val();
          const enginePower = $("#enginePower").val();
          const fuel = $("#fuel").val();
          const price = $("#price").val();
          const color = $("#color").val();
          const age = $("#age").val();
          const history = $("#history").val();

          // Send AJAX request to update.php with updated data
          $.ajax({
            type: "POST",
            url: "update.php",
            data: {
              id: id,
              model: model,
              enginePower: enginePower,
              fuel: fuel,
              price: price,
              color: color,
              age: age,
              history: history,
            },
            success: function (response) {
              $("#message").text("Car updated successfully!");
              
              },

            error: function () {
              $("#message").text("Error updating car. Please try again.");
            },
          });
        });
      });
    </script>
  </body>
</html>
