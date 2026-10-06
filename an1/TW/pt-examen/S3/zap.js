window.onload = function() {
    const canvas = document.getElementById("tv");
    const ctx = canvas.getContext("2d");

    const infoDiv = document.createElement("div");
    document.body.appendChild(infoDiv);
    infoDiv.style.marginTop = "20px";
    infoDiv.style.marginLeft = "100px";
    infoDiv.style.display = "block";

    infoDiv.style.alignItems = "center";
    infoDiv.style.justifyContent = "center";
    infoDiv.style.gap = "20px";
    infoDiv.style.fontSize = "18px";
    infoDiv.style.fontWeight = "bold";

    const detailsDiv = document.createElement("div");
    document.body.appendChild(detailsDiv);
    detailsDiv.style.marginTop = "20px";
    detailsDiv.style.marginLeft = "100px";
    detailsDiv.style.display = "block";
    

    draw();

    let matches = [];
    fetch("zap.json")
        .then(response => response.json())
        .then(data => {
            filme = data;

            canvas.addEventListener("click", () => {
                if (filme.length === 0) return;

                const film = filme[Math.floor(Math.random() * filme.length)];
                infoDiv.innerHTML = "";

                const data = document.createElement("p");
                data.textContent = film.date;
                infoDiv.appendChild(data);

                const ora = document.createElement("p");
                ora.textContent = film.time;
                infoDiv.appendChild(ora);

                const nume = document.createElement("p");
                nume.textContent = film.title;
                infoDiv.appendChild(nume);

                const poster = document.createElement("img");
                poster.src = film.poster;
                poster.style.width = "80px";
                poster.style.cursor = "pointer";
                infoDiv.appendChild(poster);

                poster.addEventListener("mouseenter", () => {
                    detailsDiv.textContent = film.starring + film.rate;
                });
                poster.addEventListener("mouseleave", () => {
                    detailsDiv.textContent = "";
                });

            });

        })
        .catch(err => console.error("Eroare la fetch:", err));

             
    function draw() {
        ctx.fillStyle = "white";
        ctx.fillRect(100, 100, 400, 300);
        ctx.fillStyle = "orange";
        ctx.fillRect(110, 110, 380, 280);

        ctx.strokeStyle = "white";
        ctx.lineWidth = 5; 
        ctx.beginPath();
        ctx.arc(300, 250, 50, 0, Math.PI * 2); 
        ctx.stroke(); 

        ctx.strokeStyle = "white"; 
        ctx.lineWidth = 5;   
        ctx.beginPath();
        ctx.moveTo(300, 100);  // punctul de start
        ctx.lineTo(300, 400); // punctul final
        ctx.stroke();   
        
        ctx.strokeStyle = "white";
        ctx.lineWidth = 5;

        ctx.beginPath();
        ctx.arc(100, 250, 100, 3 * Math.PI / 2, Math.PI / 2); // x, y, raza, startAngle, endAngle
        ctx.stroke();

        ctx.beginPath();
        ctx.arc(500, 250, 100, Math.PI / 2, 3 * Math.PI / 2); // x, y, raza, startAngle, endAngle
        ctx.stroke();

        ctx.strokeStyle = "white";
        ctx.lineWidth = 5; // grosimea liniei
        ctx.strokeRect(105, 220, 60, 60);
   }          
}   
        
       
      
