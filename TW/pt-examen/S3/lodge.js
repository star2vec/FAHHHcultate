window.onload = function() {
    const canvas = document.getElementById("lodge");
    const ctx = canvas.getContext("2d");

    const infoDiv = document.createElement("div");
    document.body.appendChild(infoDiv);
    infoDiv.style.marginTop = "20px";
    infoDiv.style.marginLeft = "100px";
    infoDiv.style.display = "block";

    draw();

    let quotes = [];
    fetch("quotes.json")
        .then(response => response.json())
        .then(data => {
            quotes = data;
        })
        .catch(err => console.error("Eroare la fetch:", err));

    const trandafir = document.createElement("img");
    trandafir.src = "rose.webp";
    trandafir.style.position = "absolute";
    trandafir.style.left = canvas.offsetLeft + (canvas.width - 200)/2 + "px";
    trandafir.style.top = canvas.offsetTop + (canvas.height - 100)/2 + "px";
    trandafir.style.width = "200px";
    trandafir.style.height = "100px";

    document.body.appendChild(trandafir);

    trandafir.addEventListener("click", () => {
        const quote = quotes[Math.floor(Math.random() * quotes.length)];

        infoDiv.innerHTML = "";

        const p = document.createElement("p");
        p.innerHTML = `<strong>${quote.character}: </strong> ${quote.quote}`;

        const details = document.createElement("span");
        details.textContent = ` (Sezon: ${quote.season}, Episod: ${quote.episode})`;
        details.style.fontStyle = "italic";
        details.style.display = "none"; // ascuns inițial

        p.appendChild(details);

        p.addEventListener("mouseenter", () => {
            details.style.display = "inline";
        });
        p.addEventListener("mouseleave", () => {
            details.style.display = "none";
        });

        infoDiv.appendChild(p);
    });


    function draw() {
        ctx.fillStyle = "white";
        ctx.fillRect(100, 100, 400, 300);
        ctx.fillStyle = "red";
        ctx.fillRect(110, 110, 380, 280);

        ctx.strokeStyle = "black";   
        ctx.lineWidth = 10;          

        const startX = 110;
        const startY = 280;
        const stepX = 30;   
        const stepY = 20;   
        const zigzags = 13; 

        ctx.beginPath();
        ctx.moveTo(startX, startY);

        for (let i = 0; i < zigzags; i++) {
            let nextX = startX + stepX * (i + 1);
            let nextY = (i % 2 === 0) ? startY - stepY : startY + stepY;
            ctx.lineTo(nextX, nextY);
        }

        ctx.stroke();
    }          
}
