document.addEventListener("DOMContentLoaded", () => {
  console.log("Opgestart");
  var index_table = 0;
  var json_table = document.getElementById("table-body");

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
          addToTable(json_table, index_table++, i.name, i.submit_date);
        });
      });
    })
    .catch((error) => {
      console.log("Error bij fetch:", error.message);
    });

  document.forms["form-id"].addEventListener("submit", (event) => {
    event.preventDefault();
    // TODO do something here to show user that form is being submitted
    fetch(event.target.action, {
      method: "POST",
      body: new URLSearchParams(new FormData(event.target)), // event.target is the form
    })
      .then((resp) => {
        return resp.json(); // or resp.text() or whatever the server sends
      })
      .then((body) => {
        // TODO handle body
        console.log(body);
        addToTable(json_table, index_table++, body.name, body.submit_date);
      })
      .catch((error) => {
        // TODO handle error
        console.log(error);
      });
  });

  function addToTable(table, index, name, date) {
    table.innerHTML += `<tr> <td>${index}</td> <td>${name}</td> <td>${date}</td></tr>`;
  }
});
