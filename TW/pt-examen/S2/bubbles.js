let nrows = 6;
let ncols = 10;
let tabla;

function createBubbleCell() {
    const cell = document.createElement("td");
    cell.style.padding = "2px";

    const img = document.createElement("img");
    img.src = "bubble-1.png";
    img.style.width = "50px";
    img.style.cursor = "pointer";

    // click pe bulă: sparge și dispare după 1s
    img.addEventListener("click", function() {
        const clickedImg = this;
        clickedImg.src = "bubble-2.png"; // imagine spartă
        setTimeout(() => {
            clickedImg.style.display = "none"; // dispare complet
        }, 1000);
    });

    cell.append(img);
    return cell;
}

function drawTable(nrows, ncols) {
    tabla = document.createElement("table");
    tabla.style.borderCollapse = "collapse";

    for (let l = 0; l < nrows; l++) {
        const row = document.createElement("tr");
        for (let c = 0; c < ncols; c++) {
            row.append(createBubbleCell());
        }
        tabla.append(row);
    }

    document.body.append(tabla);
}

// sparge o bula aleatoare
function popRandomBubble() {
    const rows = tabla.rows;
    const randRow = Math.floor(Math.random() * rows.length);
    const randCol = Math.floor(Math.random() * rows[0].cells.length);
    const img = rows[randRow].cells[randCol].querySelector("img");

    img.src = "bubble-2.png";
    setTimeout(() => {
        img.style.display = "none"; // dispare după 1s
    }, 1000);
}

// derulează banda cu un rând
function scrollRow() {
    tabla.deleteRow(0); // șterge primul rând

    const newRow = document.createElement("tr");
    for (let c = 0; c < ncols; c++) {
        newRow.append(createBubbleCell());
    }
    tabla.append(newRow);
}

// reset animat
function reset() {
    let i = 0;
    const totalRows = tabla.rows.length;
    const interval = setInterval(() => {
        if (i < totalRows) {
            scrollRow();
            i++;
        } else {
            clearInterval(interval);
        }
    }, 500);
}

// tastatura
window.addEventListener("keydown", function(e) {
    if (e.key === "b") popRandomBubble();
    else if (e.key === "n") scrollRow();
    else if (e.key === "r") reset();
});

window.onload = function() {
    drawTable(nrows, ncols);
};
