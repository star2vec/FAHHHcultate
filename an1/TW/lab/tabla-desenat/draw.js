function drawTable(nrows, ncols) {
   const container = document.getElementById("container");
   container.innerHTML = ""; 

   const table = document.createElement("table");
   
   for (let r = 0; r < nrows; r++) {
      const tr = document.createElement("tr");
      tr.classList.add(`r${r}`);

      for (let c = 0; c < ncols; c++) {
         const td = document.createElement("td");
         td.classList.add(`r${r}`, `c${c}`);
         tr.appendChild(td);
      }
      table.appendChild(tr);
   }      
   container.appendChild(table);
}

function colorCol(column, color) {
   const cells = document.querySelectorAll(`.c${column}`);
   cells.forEach(cell => cell.style.backgroundColor = color);
}

function colorRow(row, color) {
   const cells = document.querySelectorAll(`.r${row}`);
   cells.forEach(cell => cell.style.backgroundColor = color);
}

function rainbow(target) {
   let colors = ["rgb(255, 0, 0)", "rgb(255, 154, 0)", "rgb(240, 240, 0)", "rgb(79, 220, 74)", "rgb(63, 218, 216)", "rgb(47, 201, 226)", "rgb(28, 127, 238)", "rgb(95, 21, 242)", "rgb(186, 12, 248)", "rgb(251, 7, 217)"];

   if (target === "vertical") {
      const table = document.querySelector("table");
      const ncols = table.rows[0].cells.length;
      const colorsPerCol = Math.floor(ncols / colors.length);
      let extra = ncols % colors.length; // coloane rămase după împărțire

      let colIndex = 0;
      for (let i = 0; i < colors.length; i++) {
         let count = colorsPerCol + (extra > 0 ? 1 : 0);
         extra--;
         for (let j = 0; j < count; j++) {
            colorCol(colIndex, colors[i]);
            colIndex++;
         }
      }
    }

   if (target === "horizontal") {
      const table = document.querySelector("table");
      const nrows = table.rows.length;
      const colorsPerRow = Math.floor(nrows / colors.length);
      let extra = nrows % colors.length;

      let rowIndex = 0;
      for (let i = 0; i < colors.length; i++) {
         let count = colorsPerRow + (extra > 0 ? 1 : 0);
         extra--;
         for (let j = 0; j < count; j++) {
            colorRow(rowIndex, colors[i]);
            rowIndex++;
         }
      }
   }
}

function getNthChild(element, n) {
   return element.children[n] || null;
};

function drawPixel(row, col, color) {	
   const cell = document.querySelector(`.r${row}.c${col}`);
   if (cell) {
     cell.style.backgroundColor = color;
   }
}

function drawLine(r1, c1, r2, c2, color) {
   if (r1 === r2) {
      let start = Math.min(c1, c2);
      let end = Math.max(c1, c2);
      for (let c = start; c <= end; c++) {
         drawPixel(r1, c, color);
      }
   } else if (c1 === c2) {
      let start = Math.min(r1, r2);
      let end = Math.max(r1, r2);
      for (let r = start; r <= end; r++) {
        drawPixel(r, c1, color);
      }
   } else {
      console.warn("drawLine: numai linii orizontale sau verticale sunt suportate.");
   }
}

function drawRect(r1, c1, r2, c2, color) {
   drawLine(r1, c1, r1, c2, color); 
   drawLine(r2, c1, r2, c2, color); 
   drawLine(r1, c1, r2, c1, color); 
   drawLine(r1, c2, r2, c2, color);
}

function drawPixelExt(row, col, color) {
   const table = document.querySelector("table");
   let nrows = table ? table.rows.length : 0;
   let ncols = table && nrows > 0 ? table.rows[0].cells.length : 0;

   if (row >= nrows) {
      const container = document.getElementById("container");
      if (!table) {
         drawTable(0, 0); 
      }
      for (let r = nrows; r <= row; r++) {
         const tr = document.createElement("tr");
         tr.classList.add(`r${r}`);
         for (let c = 0; c < ncols; c++) {
            const td = document.createElement("td");
            td.classList.add(`r${r}`, `c${c}`);
            tr.appendChild(td);
            }
            table.appendChild(tr);
        }
        nrows = row + 1;
   }

   if (col >= ncols) {
      for (let r = 0; r < nrows; r++) {
         const tr = table.rows[r];
         for (let c = ncols; c <= col; c++) {
            const td = document.createElement("td");
            td.classList.add(`r${r}`, `c${c}`);
            tr.appendChild(td);
         }
      }
   }

   drawPixel(row, col, color);
}

function colorMixer(colorA, colorB, amount){
   let cA = colorA * (1 - amount);
   let cB = colorB * (amount);
   return parseInt(cA + cB);
}

function drawPixelAmount(row, col, color, amount) {
   const cell = document.querySelector(`.r${row}.c${col}`);
   if (!cell) return; 

   let currentColor = getComputedStyle(cell).backgroundColor; 
   let currentRGB = currentColor.match(/\d+/g).map(Number); 

   let newRGB = color.match(/\d+/g).map(Number); 

   let mixedRGB = [
      colorMixer(currentRGB[0], newRGB[0], amount),
      colorMixer(currentRGB[1], newRGB[1], amount),
      colorMixer(currentRGB[2], newRGB[2], amount)
   ];

   cell.style.backgroundColor = `rgb(${mixedRGB[0]}, ${mixedRGB[1]}, ${mixedRGB[2]})`;
}

function delRow(row) {
/*
   10. Ștergeți linia cu numărul 'row' din tabla de desenat.
*/
}

function delCol(col) {
/*
   10. Ștergeți coloana cu numărul 'col' din tabla de desenat.
*/
}

function shiftRow(row, pos) {
/*
   11. Aplicați o permutare circulară la dreapta cu 'pos' poziții a
   elementelor de pe linia cu numărul 'row' din tabla de desenat. 
*/
}

function jumble() {
/*
   12. Folosiți funcția 'shiftRow' pentru a aplica o permutare circulară
   cu un număr aleator de poziții fiecărei linii din tabla de desenat.
*/
}

function transpose() {
/*
   13. Transformați tabla de desenat în transpusa ei.
*/
}

function flip(element) {
/*
   14. Inversați ordinea copiilor obiectului DOM 'element' primit ca argument.
*/
}

function mirror() {
/*
   15. Oglindiți pe orizontală tabla de desenat: luați jumătatea stângă a tablei, 
   aplicați-i o transformare flip și copiați-o în partea dreaptă a tablei.
*/
}

function smear(row, col, amount) {
/*
   16. Întindeți culoarea unei celule de pe linia 'row' și coloana 'col' în celulele
   învecinate la dreapta, conform ponderii date de 'amount' (valoare între 0 și 1).
   Cu colorarea fiecărei celule la dreapta, valoarea ponderii se înjumătățește. 
   Hint: folosiți funcția 'drawPixelAmount'.
*/
}


window.onload = function(){
   const rows = 30;
   const cols = 30;	
   const target = "vertical";
    
   drawTable(rows, cols); 
   rainbow(target);

   drawPixelExt(1, 1, "red");

    // Test drawPixelExt: colorează o celulă care nu există încă (extinde tabela)
    drawPixelExt(40, 40, "blue"); // va extinde rânduri și coloane

    // Test drawRect: desenează un dreptunghi care încape în tabela curentă
    drawRect(0, 0, 2, 2, "green");

    // Test drawRect: desenează un dreptunghi care depășește tabela inițială
    drawRect(3, 3, 20, 20, "orange"); // se va extinde automat

    drawPixelAmount(1, 0, "rgba(51, 0, 255, 1)", 0.5);
    
}


