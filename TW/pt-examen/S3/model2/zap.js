const tvDiv = document.getElementById("tv");

// creăm un container pentru afișarea filmului
const movieInfo = document.createElement("div");
movieInfo.id = "movie-info";
movieInfo.style.marginTop = "20px";
tvDiv.after(movieInfo); // plasăm sub televizor

tvDiv.addEventListener("click", () => {
    fetch("./zap.json")
        .then(function(response) {
            return response.json();
        })
        .then(function(data) {
            // alegem un film aleator
            const randomIndex = Math.floor(Math.random() * data.length);
            const selectedMovie = data[randomIndex];

            // folosim data și ora din JSON direct
            var movieDate = selectedMovie.date;
            var movieTime = selectedMovie.time;

            // afișăm titlul, data, ora și posterul
            movieInfo.innerHTML = "<h3>" + selectedMovie.title + "</h3>" +
                                  "<p>" + movieDate + " - " + movieTime + "</p>" +
                                  "<img src='" + selectedMovie.poster + "' alt='" + selectedMovie.title + "' style='width:200px;'>";
        })
        .catch(function(err) {
            console.error("Eroare la fetch:", err);
        });
});