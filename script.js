document.addEventListener("DOMContentLoaded", () => {
  console.log("Opgestart");

  fetch("http://rpi-Melvin/CGIRPI/file.json")
    .then((response) => {
      if (!response.ok) {
        console.log(
          "Looks like there was a problem. Status Code: " + response.status
        );
        return;
      }

      response.json().then((data) => {
        // Voor elk datapunt in array table row aanmaken
        data.forEach((i) => {
          console.log(i);
          document.getElementById(
            "table-body"
          ).innerHTML += `<tr> <td>${i.id}</td> <td>${i.name}</td> <td>${i.submit_time}</td></tr>`;
        });
      });
    })
    .catch((error) => {
      console.log("Error bij fetch:", error.message);
    });
});
