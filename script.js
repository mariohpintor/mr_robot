const CONFIG = {
    startHour: 9,
    lunchStartHour: 13,
    lunchEndHour: 14,
    endHour: 18,
    quotes: [
        "¿Ya es hora de los chimichangas?",
        "Máximo esfuerzo. Mínimo salario.",
        "El trabajo en equipo está sobrevalorado. Pero tú sigue así.",
        "¿Crees que Ryan Reynolds trabaja tanto? Spoiler: No.",
        "Un gran poder conlleva una gran necesidad de siesta.",
        "Falta poco... bueno, algo falta.",
        "No olvides pestañear, es gratis.",
        "Si te rindes ahora, el código gana.",
        "Estoy vigilando esa barra de progreso. Se encoge más rápido que mi paciencia.",
        "¿Café? Yo prefiero tequila, pero tú toma café.",
        "Huele a éxito... o a tacos. Espero que sean tacos.",
        "Trabajar duro o trabajar inteligente... ¿por qué no ninguna?",
        "Solo unas horas más para ser libre como yo.",
        "Tu teclado suena bonito. Sigue así.",
        "¿Ese bug me acaba de guiñar el ojo?",
        "Recuerda: Si el código compila a la primera, sospecha.",
        "No me pagan lo suficiente para esto... a ti tampoco.",
        "El código espagueti es mi plato favorito.",
        "¿Has probado a apagarlo y encenderlo? Ah, espera, eso soy yo.",
        "Hoy es un buen día para romper producción.",
        "¿Error 404? Mi motivación no encontrada.",
        "Escribe código como si el que lo fuera a mantener fuera un psicópata que sabe dónde vives (yo).",
        "Ctrl+C, Ctrl+V, la base de la ingeniería moderna.",
        "Si funciona, no lo toques. Regla de oro."
    ],
    hourlyMessages: [
        "¡Una hora menos! ¡Vamos!",
        "Tic Tac. El tiempo vuela (cuando te diviertes, supongo).",
        "Menos tiempo en el reloj, más cerca de la libertad.",
        "¡Otra hora conquistada! Eres una máquina."
    ]
};

// Elements
const progressBar = document.getElementById('progress-bar');
const percentageText = document.getElementById('percentage-text');
const timeDisplay = document.getElementById('current-time');
const countdownDisplay = document.getElementById('countdown');
const workStatus = document.getElementById('work-status');
const messageBubble = document.getElementById('message-bubble');
const mascot = document.getElementById('mascot');
const refreshBtn = document.getElementById('refresh-msg-btn');

let lastHourCheck = -1;

function init() {
    updateTimer();
    setInterval(updateTimer, 1000); // Main loop

    // Initial message
    showRandomMessage();

    // Generate Markers
    generateMarkers();

    // Event listeners
    refreshBtn.addEventListener('click', showRandomMessage);
    mascot.addEventListener('click', () => {
        showRandomMessage();
        animateMascot();
    });
}

function generateMarkers() {
    const track = document.getElementById('progress-track');
    // Remove existing markers (except progress-fill which is first child)
    // Actually safer to just append to it, assuming HTML is clean (we cleaned it).

    const start = CONFIG.startHour;
    const end = CONFIG.endHour;
    const totalDuration = end - start;

    for (let h = start + 1; h < end; h++) {
        const percent = ((h - start) / totalDuration) * 100;

        const marker = document.createElement('div');
        marker.className = 'marker';
        marker.style.left = `${percent}%`;

        // Label logic
        let hourLabel = h > 12 ? `${h - 12}pm` : `${h}am`;
        if (h === 12) hourLabel = '12pm';

        // Add taco to 1pm
        if (h === 13) hourLabel = '🌮 ' + hourLabel;

        const labelSpan = document.createElement('span');
        labelSpan.className = 'marker-label';
        labelSpan.textContent = hourLabel;

        marker.appendChild(labelSpan);
        track.appendChild(marker);
    }
}

function updateTimer() {
    const now = new Date();
    // For debugging/testing at different times, uncomment below:
    // now.setHours(13, 30, 0); 

    const currentHour = now.getHours();
    const currentMin = now.getMinutes();
    const currentSec = now.getSeconds();

    // Display formatted time
    timeDisplay.textContent = now.toLocaleTimeString('es-MX', { hour12: true });

    // Calculate minutes from start of day (00:00)
    const currentTotalMinutes = currentHour * 60 + currentMin + (currentSec / 60);

    // Define markers in minutes
    const startMinutes = CONFIG.startHour * 60;
    const lunchStartMinutes = CONFIG.lunchStartHour * 60;
    const lunchEndMinutes = CONFIG.lunchEndHour * 60;
    const endMinutes = CONFIG.endHour * 60;

    let progress = 0;
    let statusMsg = "En turno";
    let timeLeftMsg = "";

    // Logic for State
    if (currentTotalMinutes < startMinutes) {
        // Before work
        progress = 100;
        statusMsg = "Dormido / No ha empezado";
        const minsUntilStart = Math.ceil(startMinutes - currentTotalMinutes);
        timeLeftMsg = `Empieza en ${Math.floor(minsUntilStart / 60)}h ${minsUntilStart % 60}m`;
    } else if (currentTotalMinutes >= endMinutes) {
        // After work
        progress = 0;
        statusMsg = "¡LIBRE!";
        timeLeftMsg = "¡Vete a casa!";
    } else {
        // During work day (09:00 - 18:00)

        // Calculate progress based on the full range (9h duration from 9 to 18)
        const totalWorkDuration = endMinutes - startMinutes;
        const elapsed = currentTotalMinutes - startMinutes;
        // Invert logic: 100% at start, 0% at end. Representing "Battery" or "Energy"
        progress = 100 - ((elapsed / totalWorkDuration) * 100);

        // Specific checks
        if (currentTotalMinutes >= lunchStartMinutes && currentTotalMinutes < lunchEndMinutes) {
            statusMsg = "HORA DE COMIDA 🌮";
            // Pulse effect can be added via CSS class if needed
        } else {
            statusMsg = "Modo Productivo";
        }

        // Time Left calculation
        const minsLeft = Math.ceil(endMinutes - currentTotalMinutes);
        const hoursLeft = Math.floor(minsLeft / 60);
        const minutesLeftPart = minsLeft % 60;
        timeLeftMsg = `Faltan ${hoursLeft}h ${minutesLeftPart}m`;

        // Hourly Check logic
        if (currentMin === 0 && currentSec === 0 && currentHour !== lastHourCheck) {
            lastHourCheck = currentHour;
            triggerHourlyMessage();
        }
    }

    // Update DOM
    progressBar.style.width = `${progress}%`;
    percentageText.textContent = `${Math.floor(progress)}%`;
    workStatus.textContent = statusMsg;
    countdownDisplay.textContent = timeLeftMsg;

    // Change status color for Lunch
    if (statusMsg.includes("COMIDA")) {
        workStatus.style.color = "#FFD700"; // Gold
        progressBar.style.filter = "hue-rotate(90deg)"; // Change bar color temporarily
    } else {
        workStatus.style.color = "var(--text-white)";
        progressBar.style.filter = "none";
    }
}

function showRandomMessage() {
    const quotes = CONFIG.quotes;
    const randomIndex = Math.floor(Math.random() * quotes.length);
    updateBubble(quotes[randomIndex]);
}

function triggerHourlyMessage() {
    const msgs = CONFIG.hourlyMessages;
    const randomIndex = Math.floor(Math.random() * msgs.length);
    updateBubble(msgs[randomIndex]);
    animateMascot();
}

function updateBubble(text) {
    messageBubble.style.animation = 'none';
    messageBubble.offsetHeight; /* trigger reflow */
    messageBubble.textContent = text;
    messageBubble.style.animation = 'popIn 0.5s cubic-bezier(0.175, 0.885, 0.32, 1.275)';
}

function animateMascot() {
    mascot.style.transform = "scale(1.1) rotate(5deg)";
    setTimeout(() => {
        mascot.style.transform = "scale(1) rotate(0deg)";
    }, 200);
}

// Start
init();
