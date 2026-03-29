let totaldance = parseInt(localStorage.getItem("totaldance")) || 0;
const counterEl = document.getElementById("counter");
counterEl.textContent = totaldance;

document.addEventListener("keydown", function(event) {
    const key = event.key.toLowerCase();
    if (key=='b') {
        const badger = document.createElement("img");
        badger.src = "badger-1.png"; 
        badger.style.position = "absolute"; 
        badger.style.width = "200px";        
        badger.style.height = "auto";

        const maxX = window.innerWidth - 200; 
        const maxY = window.innerHeight - 200; 
        const x = Math.random() * maxX;
        const y = Math.random() * maxY;

        badger.style.left = x + "px";
        badger.style.top = y + "px";

        document.body.appendChild(badger);



        let dancing = false;
        let intervalId;

        const danceImages = [
            "badger-2.png",
            "badger-3.png",
            "badger-4.png",
            "badger-1.png"
        ];

        badger.addEventListener("click", function() {
            if (!dancing) {
                dancing = true;
                let index = 0;

                function danceCycle() {
                    intervalId = setInterval(() => {
                        badger.src = danceImages[index];
                        index++;
                        if (index >= danceImages.length) {
                            clearInterval(intervalId);
                            index = 0;
                            totaldance++;
                            localStorage.setItem("totaldance", totaldance);
                            counterEl.textContent = totaldance;
                            // pauza de 1s înainte de următorul ciclu
                            setTimeout(danceCycle, 1000);
                        }
                    }, 200);
                }

                danceCycle(); 
            } else {
                dancing = false;
                clearInterval(intervalId);
                badger.remove();
            }
        });
    }
});
