const container = document.getElementById("movie-list");

fetch("cinemateca.xml")
  .then(response => {
    if (!response.ok) throw new Error("Nu s-a putut încărca XML-ul!");
    return response.text();
  })
  .then(xmlString => {
    const parser = new DOMParser();
    const xmlDoc = parser.parseFromString(xmlString, "text/xml");

    const films = Array.from(xmlDoc.getElementsByTagName("film")).map(film => {
      return {
        titlu: film.getElementsByTagName("titlu")[0].textContent,
        titluLang: film.getElementsByTagName("titlu")[0].getAttribute("lang"),
        gen: film.getElementsByTagName("gen")[0].textContent,
        regizor: film.getElementsByTagName("regizor")[0].textContent,
        an: film.getElementsByTagName("an_lansare")[0].textContent,
        scenarist: film.getElementsByTagName("scenarist")[0].textContent,
        producator: film.getElementsByTagName("producator")[0].textContent,
        actori: Array.from(film.getElementsByTagName("actor")).map(a => ({
          nume: a.textContent,
          rol: a.getAttribute("rol")
        })),
        scor: film.getElementsByTagName("scor")[0].textContent
      };
    });

    films.forEach(film => {
      const ul = document.createElement("ul");
      ul.innerHTML = `
        <li><strong>Titlu:</strong> ${film.titlu} (${film.titluLang})</li>
        <li><strong>Gen:</strong> ${film.gen}</li>
        <li><strong>Regizor:</strong> ${film.regizor}</li>
        <li><strong>An lansare:</strong> ${film.an}</li>
        <li><strong>Scenarist:</strong> ${film.scenarist}</li>
        <li><strong>Producător:</strong> ${film.producator}</li>
        <li><strong>Actori:</strong>
          <ul>
            ${film.actori.map(a => `<li>${a.nume} (${a.rol})</li>`).join("")}
          </ul>
        </li>
        <li><strong>Scor:</strong> ${film.scor}</li>
      `;
      container.appendChild(ul);
    });

  })
  .catch(error => {
    container.textContent = "Eroare la încărcarea fișierului XML: " + error;
  });
