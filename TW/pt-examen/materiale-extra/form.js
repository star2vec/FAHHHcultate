
window.onload = function() {
  const slider = document.getElementById("credit");
  const labelval = document.getElementById("credit-value");

  labelval.textContent = slider.value;

  slider.addEventListener("input", function() {
    labelval.textContent = slider.value;
  });

  const colorInput = document.getElementById("color");

  const savedColor = localStorage.getItem("bgColor");
  if (savedColor) {
    colorInput.value = savedColor;
    document.body.style.backgroundColor = savedColor;
  }

  colorInput.addEventListener("input", function() {
    document.body.style.backgroundColor = colorInput.value;
    localStorage.setItem("bgColor", colorInput.value);
  });



  const form = document.querySelector("form");
  const buton = document.getElementById("submit-btn");

  buton.addEventListener("click", function() {
    let valid = form.checkValidity(); 

    if (!valid) {
      alert("wrong >:( completeaza cum trebuie!!");
      return;
    }

    const container = document.getElementById("container");
    container.innerHTML = "<h2>date trimise cu succes ^_^</h2>";
  });
};

