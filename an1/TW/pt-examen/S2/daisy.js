const table = document.createElement("table");
const row = document.createElement("tr");
const cell = document.createElement("td");

const img = document.createElement("img");
img.src = "daisy.png";
img.style.width = "800px";

cell.appendChild(img);
row.appendChild(cell);
table.appendChild(row);
document.body.appendChild(table);

flowers = [img]

document.addEventListener("keydown", function(event) {
    const key = event.key.toLowerCase();
    
    if (key=='b') {
        const randomidx = Math.floor(Math.random() * flowers.length);
        const chosen = flowers[randomidx];
        
                const parentCell = chosen.parentElement;
        const parentRow = parentCell.parentElement;
        const rowIndex = Array.from(table.rows).indexOf(parentRow);
        const cellIndex = Array.from(parentRow.cells).indexOf(parentCell);

        // dimensiunea nouă
        const newSize = parseInt(chosen.style.width) / 2;

        // ștergem floarea originală
        chosen.remove();
        flowers.splice(randomidx, 1);

        // ștergem celula originală
        parentRow.removeChild(parentCell);

        // creăm două rânduri noi dacă e nevoie
        const newRow1 = document.createElement("tr");
        const newRow2 = document.createElement("tr");

        for (let i = 0; i < 2; i++) {
            const newCell1 = document.createElement("td");
            const newImg1 = document.createElement("img");
            newImg1.src = "daisy.png";
            newImg1.style.width = newSize + "px";
            newCell1.appendChild(newImg1);
            newRow1.appendChild(newCell1);
            flowers.push(newImg1);

            const newCell2 = document.createElement("td");
            const newImg2 = document.createElement("img");
            newImg2.src = "daisy.png";
            newImg2.style.width = newSize + "px";
            newCell2.appendChild(newImg2);
            newRow2.appendChild(newCell2);
            flowers.push(newImg2);
        }

        // înlocuim rândul original cu cele 2 rânduri noi
        table.insertBefore(newRow1, table.rows[rowIndex]);
        table.insertBefore(newRow2, table.rows[rowIndex + 1]);
    }
});