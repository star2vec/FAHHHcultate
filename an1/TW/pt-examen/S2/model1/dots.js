let totalDots = parseInt(localStorage.getItem("totalDots")) || 0;
const counterEl = document.getElementById("counter");
counterEl.textContent = totalDots;


function ondotclick(dot) {
   const color = dot.style.backgroundColor;
   const size = dot.style.width;

   
   const newDot = document.createElement("div");
   newDot.style.width = newDot.style.height = size;
   newDot.style.backgroundColor = color;
   newDot.style.borderRadius = "50%";
   newDot.style.position = "absolute";

   const sizeNum = parseFloat(size); // transformăm "50px" în 50
   const x = Math.random() * (window.innerWidth - sizeNum);
   const y = Math.random() * (window.innerHeight - sizeNum);
   newDot.style.left = x + "px";
   newDot.style.top = y + "px";

   newDot.addEventListener("click", function() {
       ondotclick(newDot);
   });

   totalDots++;
   localStorage.setItem("totalDots", totalDots);
   counterEl.textContent = totalDots;

   document.body.appendChild(newDot);
}

document.addEventListener("keydown", function(event) {
    const key = event.key.toLowerCase();
    const colors = {r: "red", g: "green", y: "yellow", b: "blue"};

    if (colors[key]) {
        const marime = document.getElementById("size").value;

        const dot = document.createElement("div");
        dot.style.width = dot.style.height = marime + "px";
        dot.style.backgroundColor = colors[key];
        dot.style.borderRadius = "50%";
        dot.style.position = "absolute";

        const x = Math.random() * (window.innerWidth - marime);
        const y = Math.random() * (window.innerHeight - marime);
        dot.style.left = x + "px";
        dot.style.top = y + "px";

        dot.addEventListener("click", function() {
            ondotclick(dot);
        });

        totalDots++;
         localStorage.setItem("totalDots", totalDots);
         counterEl.textContent = totalDots;

        document.body.appendChild(dot);
    }
});
