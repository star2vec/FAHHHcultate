function drawTable(nrows, ncols) {
   let l, c;

   const container = document.getElementById("container")
   const tabla = document.createElement("table")

   for (l=0; l<nrows; l++) {
      const lin = document.createElement("tr")
      for (c=0; c<ncols; c++) {
         const cell = document.createElement("td")

         cell.classList.add("l" + l); 
         cell.classList.add("c" + c); 

         lin.append(cell)
      }
      tabla.append(lin);
   }

   container.append(tabla)
}

function colorCol(column, color) {
   let i;
   const cells = document.querySelectorAll(".c" + column);

   for (let i = 0; i < cells.length; i++) {
      cells[i].style.backgroundColor = color;
   }
}

function colorRow(row, color) {
   let i;
   const cells = document.querySelectorAll(".l" + row);

   for (let i = 0; i < cells.length; i++) {
      cells[i].style.backgroundColor = color;
   }
}

function rainbow(target) {
   let colors = ["rgb(255, 0, 0)", "rgb(255, 154, 0)", "rgb(240, 240, 0)", "rgb(79, 220, 74)", "rgb(63, 218, 216)", "rgb(47, 201, 226)", "rgb(28, 127, 238)", "rgb(95, 21, 242)", "rgb(186, 12, 248)", "rgb(251, 7, 217)"];

   let nlin = document.querySelectorAll("tr").length;
   let ncol = document.querySelectorAll("tr")[0].children.length;
   let l, c;

   if (target === "horizontal") {
      for (l = 0; l < nlin; l++) {
         let colorIndex = Math.floor(l / nlin * colors.length);
         colorRow(l, colors[colorIndex]);
      }
   } else if (target === "vertical") {
      for (c = 0; c < ncol; c++) {
         let colorIndex = Math.floor(c / ncol * colors.length);
         colorCol(c, colors[colorIndex]);
      }
   }
}

function getNthChild(element, n) {
   return element.children[n-1];
};

function drawPixel(row, col, color) {
   row--;
   col--;
   let l, c;

   let nlin = document.querySelectorAll("tr").length;
   let ncol = document.querySelectorAll("tr")[0].children.length;

   const container = document.getElementById("container");
   const tabla = container.querySelector("table");

   for (l=nlin; l<=row; l++) {
      const lin = document.createElement("tr");
      for (c=0; c<ncol; c++) {
         const cell = document.createElement("td");
         cell.classList.add("l" + l);
         cell.classList.add("c" + c);
         lin.append(cell);
      }
      tabla.append(lin);
   }

   nlin = document.querySelectorAll("tr").length; 
   if (col >= ncol) {
     for (let l = 0; l < nlin; l++) {
         const lin = document.querySelectorAll("tr")[l];
         for (let c = ncol; c <= col; c++) {
            const cell = document.createElement("td");
            cell.classList.add("l" + l);
            cell.classList.add("c" + c);
            lin.append(cell);
        }
      }
    }

   const cell = document.querySelector(".l" + row + ".c" + col);
   cell.style.backgroundColor = color;
}

function drawLine(r1, c1, r2, c2, color) {
   let aux, l, c, cell;
   r1--;
   c1--;
   r2--;
   c2--;
   if (r1==r2) {
      if (c2<c1) {
         aux = c1;
         c1 = c2;
         c2 = aux;
      }
      l = r1;
      for (c=c1; c<=c2; c++) {
         cell = document.querySelector(".l" + l + ".c" + c);
         cell.style.backgroundColor = color;
      }
   }
   if (c1==c2) {
      if (r2<r1) {
         aux = r1;
         r1 = r2;
         r2 = aux;
      }
      c = c1;
      for (l=r1; l<=r2; l++) {
         cell = document.querySelector(".l" + l + ".c" + c);
         cell.style.backgroundColor = color;
      }
   }
}

function drawRect(r1, c1, r2, c2, color) {
   let l, c;
   for (l=r1; l<=r2; l++) {
      drawLine(l, c1, l, c2, color);
   }
}

function colorMixer(colorA, colorB, amount){
   let cA = colorA * (1 - amount);
   let cB = colorB * (amount);
   return parseInt(cA + cB);
}

function addClickHandlers() {
    const cells = document.querySelectorAll("td");
    for (let i = 0; i < cells.length; i++) {
        cells[i].addEventListener("click", function() {
            let l = parseInt(this.classList[0].slice(1)); 
            let c = parseInt(this.classList[1].slice(1));
            let color = document.getElementById("colorPicker").value;
            drawPixel(l+1, c+1, color); 
        });
    }
}


window.onload = function(){
    const rows = 20;
    const cols = 20;	
   
   drawTable(rows, cols);
   

   colorRow(0, "red");
   colorCol(0, "blue");
   rainbow("horizontal");
   drawPixel(3, 7, "black");

   drawLine(10, 12, 10, 15, "white");
   drawLine(5, 8, 17, 8, "white");
   drawRect(2, 2, 18, 5, "teal");

   drawPixel(25, 30, "black");

   addClickHandlers();
}


