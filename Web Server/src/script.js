document.getElementById("colorButton").addEventListener("click", function() {
    let colors = ["#ff9999", "#99ccff", "#99ff99", "#ffcc99", "#ccccff"];
    let randomColor = colors[Math.floor(Math.random() * colors.length)];
    document.body.style.backgroundColor = randomColor;
});
