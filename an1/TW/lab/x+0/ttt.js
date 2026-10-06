let nume = prompt("Hai să jucăm X și 0. Cum te cheamă?");
let simbol = prompt("Bună, " + nume + ". Cu ce vrei să joci? X sau 0? X începe primul.");
let simbolcomputer = simbol === "X" ? "0" : "X";

let tabla = [];

for (let i=0; i<9; i++) {
    tabla.push("?");
}

function win(tabla) {
    const optiuni = [
        [0,1,2], [3,4,5], [6,7,8],
        [0,3,6], [1,4,7], [2,5,8],
        [0,4,8], [2,4,6]
    ];

    for (let line of optiuni) {
        const [a, b, c] = line;
        if (tabla[a] !== "?" && tabla[a] === tabla[b] && tabla[a] === tabla[c]) {
            return tabla[a];
        }
    }

    return null; 
}

function draw(tabla) {
    return !tabla.includes("?") && win(tabla) === null;
}

function printtt(tabla) {
    let output = "";

    for (let i=0; i<9; i++) {
        let cell = tabla[i] === "?" ? (i+1) : tabla[i];

        output += "| " + cell + " ";

        if ((i+1) % 3 === 0) {
            output += "|\n";
        }
    }

    return output;
}

function computer(tabla, simbol) {
    while (true) {
        let pos = Math.floor(Math.random() * 9) + 1; 
        if (valid(pos, tabla)) {
            tabla[pos-1] = simbol;
            break;
        }
    }
}

function valid(pozitie, tabla) {
    let num = Number(pozitie);

    if (isNaN(num) || num < 1 || num > 9) {
        return false;
    }

    let idx = num-1;

    return tabla[idx] === "?";
}

while (true) {
    let poz; 

    while (true) {
        poz = prompt(printtt(tabla) + "\nUnde vrei să pui următorul semn?");
        if (valid(poz, tabla)) {
            let idx = Number(poz)-1;
            tabla[idx] = simbol;
            break; 
        } else {
            alert("Poziție invalidă. Te rog încearcă din nou.");
        }
    }

    let winner = win(tabla);
    if (winner) {
        if (winner === simbol) {
            alert("Bravo, " + nume + ", ai câștigat! gg");
        } else {
            alert("Ai pierdut :( womp womp");
        }
        break; 
    }

    if (draw(tabla)) {
        alert("Remiză!");
        break; 
    }

    computer(tabla, simbolcomputer);
    alert("Calculatorul a jucat:\n" + printtt(tabla));

    winner = win(tabla);
    if (winner) {
        if (winner === simbol) alert("Bravo, " + nume + ", ai câștigat! gg");
        else alert("Ai pierdut :( womp womp");
        break;
    }
    if (draw(tabla)) {
        alert("Remiză!");
        break;
    }
}