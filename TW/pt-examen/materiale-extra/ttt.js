let nume = prompt("Hai să jucăm X și 0. Cum te cheamă?");

let p1 = prompt("Bună, " + nume + ". Cu ce vrei să joci? X sau 0? X începe primul.")

if (p1=='X') {
    p2 = 0
} else {
    p2 = 'X'
}

let pch = [p1, p2];

let tabla = [];
for (let i = 0; i < 9; i++) {
  tabla[i] = "?";
}

function printtt(tabla) {
  let rez = "";
  let ch;

  for (let i = 0; i < 9; i++) {
    if (tabla[i] === "?") {
      ch = i + 1;
    } else {
      ch = tabla[i];
    }

    rez += "| " + ch + " ";

    if ((i + 1) % 3 === 0) {
      rez += "|\n";
    }
  }

  return rez;
}

function valid(p) {
    if (1<=p && p<=9 && tabla[p-1]=='?') {
        return true;
    }
    return false;
}

function win(tabla) {
    let l, c;

    for (l=0; l<3; l++) {
        if (tabla[l*3] !== '?' && tabla[l*3] === tabla[l*3+1] && tabla[l*3] === tabla[l*3+2]) {
            return tabla[l*3];
        }
    }
    for (c=0; c<3; c++) {
        if (tabla[c] !== '?' && tabla[c] === tabla[c+3] && tabla[c] === tabla[c+6]) {
            return tabla[c];
        }
    }
    if (tabla[0] !== '?' && tabla[0] === tabla[4] && tabla[0] === tabla[8]) {
        return tabla[0];
    }
    if (tabla[2] !== '?' && tabla[2] === tabla[4] && tabla[2] === tabla[6]) {
        return tabla[2];
    }
    return false;
}

function draw(tabla) {
    let i;

    for (i=0; i<9; i++) {
        if (tabla[i] === "?") {
            return false;
        }
    }
    
    return !win(tabla);
}

let round = 0;
let ok = 0;
while (true) {
    let poz = prompt("Unde vrei să pui următorul semn?\n" + printtt(tabla))
    poz = parseInt(poz)

    while (valid(poz)==false) {
        poz = prompt("haha wrong :P try again!!\n" + printtt(tabla))
    }
    tabla[poz-1] = pch[round%2];
    round++;

    if (win(tabla)) {
        alert("omg " + win(tabla) + " ai castigat yippee!! ^_^ congrats :333");
        break;
    }
    if (draw(tabla)) {
        alert("remiza miau :P");
        break;
    }
}

