function updateCart() {
  const k = (document.getElementById("i1")).value;
  const l = (document.getElementById("i2")).value;

  const total = k * 50 + l * 45;
  document.getElementById("total").innerHTML = total;

  if (k!= 0) {
    document.getElementById("itemsPurchased").innerHTML = k + " Pencil";
  }

  if (l!= 0) {
    document.getElementById("itemsPurchased").innerHTML = l + " Eraser";
  }

  if (k!= 0 && l!= 0) {
    document.getElementById("itemsPurchased").innerHTML = k + " Pencil and " + l + " Eraser";
  }

}

