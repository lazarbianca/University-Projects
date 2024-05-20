let isPlaying = false;
let slideIndex = 0;
let interval = 1000; // default timeout (ms)
let slideshow;
let currentSlide = 0;

startSlideshow(); // Start the slideshow automatically

function startSlideshow() {
  slideshow = setInterval(nextSlide, interval);
  document.getElementById("play-pause-btn").textContent = "Pause";
  isPlaying = true;
}

function stopSlideshow() {
  clearInterval(slideshow);
  document.getElementById("play-pause-btn").textContent = "Play";
  isPlaying = false;
}

function togglePlayPause() {
  if (isPlaying) {
    stopSlideshow();
  } else {
    startSlideshow();
  }
}

function nextSlide() {
  const slides = document.getElementsByClassName("slide");

  slides[currentSlide].style.display = "none";
  currentSlide = (currentSlide + 1) % slides.length;
  slides[currentSlide].style.display = "block";
  if (
    currentSlide === 0 &&
    !document.getElementById("replay-checkbox").checked
  ) {
    stopSlideshow();
  }
}

function changeInterval() {
  interval = parseInt(document.getElementById("interval-select").value);
  if (isPlaying) {
    stopSlideshow();
    // stop and start to reset the interval in START
    startSlideshow();
  }
}

document
  .getElementById("play-pause-btn")
  .addEventListener("click", togglePlayPause);
document
  .getElementById("interval-select")
  .addEventListener("change", changeInterval);
