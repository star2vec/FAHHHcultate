window.onload = function() {

   const gallery = document.getElementById("gallery");
   const info = document.getElementById("info");

   const albumToFile = {
        "Selected Ambient Works Volume II": "0.json",
        "Journey in Satchidananda": "1.json",
        "Trout Mask Replica": "2.json",
        "Remain in Light": "3.json",
        "Bach: The Goldberg Variations": "4.json",
        "Einstein on the Beach": "5.json",
        "Music for 18 Musicians": "6.json",
        "Head Hunters": "7.json",
        "Blood on the Tracks": "8.json",
        "Hounds of Love": "9.json",
        "Heroes": "10.json",
        "Maggot Brain": "11.json",
        "Before and After Science": "12.json",
        "The Velvet Underground & Nico": "13.json",
        "Sgt. Pepper's Lonely Hearts Club Band": "14.json"
    };

    fetch("albums.json")
    .then(response => {
      if (!response.ok) throw new Error("Nu s-a putut încărca albums.json!");
      return response.json(); // JSON, nu text
    })
    .then(albums => {

      albums.forEach(album => {
         const albumDiv = document.createElement("div");
         albumDiv.classList.add("album");

         const img = document.createElement("img");
         img.src = "images/" + album.image;
         img.alt = album.name;
         albumDiv.appendChild(img);

         const nume = document.createElement("p");
         nume.textContent = album.name;
         albumDiv.appendChild(nume);

   
         img.addEventListener("click", () => {
            const file = "albums/" + albumToFile[album.name];
            fetch(file) 
               .then(resp => {
               if (!resp.ok) throw new Error("Nu s-a putut încărca fișierul de detalii!");
               return resp.json();
               })
               .then(details => {
               info.innerHTML = `
                  <h2>${details.name}</h2>
                  <p><strong>Artist:</strong> ${details.artist}</p>
                  <p><strong>An lansare:</strong> ${details.year}</p>
                  <p><strong>Label:</strong> ${details.label}</p>
                  <p><strong>Format:</strong> ${details.format}</p>
                  <p><strong>Genuri:</strong> ${details.genres.join(", ")}</p>
                  <img src="images/${details.image}" alt="${details.name}">
               `;
               })
               .catch(err => {
               info.textContent = "Eroare la încărcarea detaliilor albumului.";
               console.error(err);
            });
         });


        gallery.appendChild(albumDiv);
      });

    })
    .catch(error => {
      gallery.textContent = "Eroare la încărcarea albumelor.";
      console.error(error);
    });

};

