let totalrabbits = parseInt(localStorage.getItem("totalrabbits")) || 0;
const counterEl = document.getElementById("counter");
counterEl.textContent = totalrabbits;


const rabbits = [];
let floatIntervalId = null;

document.addEventListener("keydown", function(event) {
    const key = event.key.toLowerCase();

    const rabbitImages = [
        "rabbit-02.png",
        "rabbit-03.png",
    ];

    if (key=='r') {
        const rabbit = document.createElement("img");
        rabbit.src = "rabbit-01.png"; 
        rabbit.style.position = "absolute"; 
        rabbit.style.width = "50px";        
        rabbit.style.height = "auto";

        const marime = 50;
        const maxX = window.innerWidth - marime; 
        const maxY = window.innerHeight - marime; 
        const x = Math.random() * maxX;
        const y = Math.random() * maxY;

        rabbit.style.left = x + "px";
        rabbit.style.top = y + "px";

        rabbit.clickIndex = 0;  
        rabbit.addEventListener("click", function() {
            if (rabbit.clickIndex < rabbitImages.length) {
                rabbit.src = rabbitImages[rabbit.clickIndex];
                rabbit.clickIndex++;
            } else {
                rabbit.remove();
            }
        });

        totalrabbits++;
        localStorage.setItem("totalrabbits", totalrabbits);
        counterEl.textContent = totalrabbits;

        rabbits.push(rabbit);
        document.body.appendChild(rabbit);
    }

    if (key === 'p') {
        if (!floatIntervalId) { 
            floatIntervalId = setInterval(() => {
                rabbits.forEach(rabbit => {
            
                    const dx = (Math.random() - 0.5) * 100; 
                    const dy = (Math.random() - 0.5) * 100;
                    const currentX = parseFloat(rabbit.style.left);
                    const currentY = parseFloat(rabbit.style.top);
                    rabbit.style.left = (currentX + dx) + "px";
                    rabbit.style.top = (currentY + dy) + "px";
                });
            }, 10); 
        }
    }
    if (key === 'p') {
        if (!floatIntervalId) { 
            floatIntervalId = setInterval(() => {
                rabbits.forEach(rabbit => {
            
                    const dx = (Math.random() - 0.5) * 100; 
                    const dy = (Math.random() - 0.5) * 100;
                    const currentX = parseFloat(rabbit.style.left);
                    const currentY = parseFloat(rabbit.style.top);
                    rabbit.style.left = (currentX + dx) + "px";
                    rabbit.style.top = (currentY + dy) + "px";
                });
            }, 10); 
        }
    }

    if (key === 's') {
        if (floatIntervalId) {
            clearInterval(floatIntervalId);
            floatIntervalId = null;
        }
    }

    if (key === 'a') {
        const sound = new Audio("rabbits-ambience.mp3");
        sound.play();
    }
});
