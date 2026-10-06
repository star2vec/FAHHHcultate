const bigball = document.getElementById("bigball");
const miniball = document.getElementById("miniball");
const answerEl = document.getElementById("answer");

bigball.addEventListener("click", function() {
    fetch("magic.json")
        .then(response => response.json())
        .then(data => {
            // alegem un răspuns aleator
            const randomIndex = Math.floor(Math.random() * data.length);
            const selected = data[randomIndex];

            // alegem culoarea în funcție de bool
            let color;
            if (selected.bool === "yes") {
                color = "green";
            } else if (selected.bool === "no") {
                color = "red";
            } else {
                color = "orange";
            }

            // setăm culoarea discului și mesajul
            miniball.style.backgroundColor = color;
            answerEl.textContent = selected.text;
            answerEl.style.color = color;

        })
        .catch(err => console.error("Eroare la fetch:", err));
});
