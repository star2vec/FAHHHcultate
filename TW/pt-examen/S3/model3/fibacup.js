window.onload = function() {
    const canvas = document.getElementById("teren");
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

    // div pentru afișarea țării la hover
    const countryDiv = document.createElement("div");
    countryDiv.style.marginTop = "5px";
    countryDiv.style.marginLeft = "100px";
    countryDiv.style.fontSize = "16px";
    countryDiv.style.fontWeight = "bold";
    document.body.appendChild(countryDiv);

    draw();

    let matches = [];
    fetch("fibacup.json")
        .then(response => response.json())
        .then(data => {
            matches = data;

            canvas.addEventListener("click", () => {
                if (matches.length === 0) return;

                const match = matches[Math.floor(Math.random() * matches.length)];
                infoDiv.innerHTML = "";

                // steag gazdă
                const homeFlag = document.createElement("img");
                homeFlag.src = match.homeflag;
                homeFlag.style.width = "80px";
                homeFlag.style.cursor = "pointer";

                // steag oaspete
                const guestFlag = document.createElement("img");
                guestFlag.src = match.guestflag;
                guestFlag.style.width = "80px";
                guestFlag.style.cursor = "pointer";

                // hover pentru homeFlag
                homeFlag.addEventListener("mouseenter", () => {
                    countryDiv.textContent = match.home;
                });
                homeFlag.addEventListener("mouseleave", () => {
                    countryDiv.textContent = "";
                });

                // hover pentru guestFlag
                guestFlag.addEventListener("mouseenter", () => {
                    countryDiv.textContent = match.guest;
                });
                guestFlag.addEventListener("mouseleave", () => {
                    countryDiv.textContent = "";
                });

                infoDiv.appendChild(homeFlag);
                infoDiv.appendChild(guestFlag);
                const br = document.createElement("br");
                infoDiv.appendChild(br);

                const dateEl = document.createElement("div");
                dateEl.textContent = `${match.date}, ${match.time}`;
                infoDiv.appendChild(dateEl);

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
        
       
      
