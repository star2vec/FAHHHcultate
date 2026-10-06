let totalburst = parseInt(localStorage.getItem("totalburst")) || 0;
const counterEl = document.getElementById("counter");
counterEl.textContent = totalburst;

const bubbles = [];
let floatIntervalId = null; 

document.addEventListener("keydown", function(event) {
    const key = event.key.toLowerCase();

    const burstImages = [
        "bubble-2.png",
        "bubble-3.png",
        "bubble-4.png"
    ];
    

    if (key=='s') {
        const bubble = document.createElement("img");
        bubble.src = "bubble-1.png"; 
        bubble.style.position = "absolute"; 
        bubble.style.width = "200px";        
        bubble.style.height = "auto";
        
        const marime = 200;
        const x = Math.random() * (window.innerWidth - marime);
        const y = Math.random() * (window.innerHeight - marime);
        bubble.style.left = x + "px";
        bubble.style.top = y + "px";

        bubble.addEventListener("click", function() {
            onbubbleclick(bubble, burstImages);
        });

        bubbles.push(bubble);
        document.body.appendChild(bubble);
    }

    if (key === 'p') {
        if (!floatIntervalId) { // dacă nu e deja pornit
            floatIntervalId = setInterval(() => {
                bubbles.forEach(bubble => {
                    // mișcare aleatorie
                    const dx = (Math.random() - 0.5) * 100; // -10 până +10 px
                    const dy = (Math.random() - 0.5) * 100;
                    const currentX = parseFloat(bubble.style.left);
                    const currentY = parseFloat(bubble.style.top);
                    bubble.style.left = (currentX + dx) + "px";
                    bubble.style.top = (currentY + dy) + "px";
                });
            }, 100); // actualizare la fiecare 100ms
        }
    }

    if (key === 'f') {
        if (floatIntervalId) {
            clearInterval(floatIntervalId);
            floatIntervalId = null;
        }
    }


});

function onbubbleclick(bubble, burstImages) {
    let index = 0;

    const intervalId = setInterval(() => {
        bubble.src = burstImages[index];
        index++;

        if (index >= burstImages.length) {
            clearInterval(intervalId);      // oprește intervalul
            bubble.remove();                // elimină balonul din ecran
            totalburst++;
            localStorage.setItem("totalburst", totalburst);
            counterEl.textContent = totalburst;
        }
    }, 200); // 200ms între cadre
}
