let currentQuestionIndex = 0;
let correctAnswers = 0;

const questions = [
    {
        question: "What is the capital of France?",
        options: ["Paris", "London", "Berlin", "Madrid"],
        answer: "Paris"
    },
    {
        question: "What is 2 + 2?",
        options: ["3", "4", "5", "6"],
        answer: "4"
    },
    {
        question: "Who wrote Hamlet?",
        options: ["William Shakespeare", "Charles Dickens", "Leo Tolstoy", "Mark Twain"],
        answer: "William Shakespeare"
    }
];

function displayQuestion() {
    const quizContainer = document.getElementById('quiz-container');
    const questionObj = questions[currentQuestionIndex];

    let optionsHtml = questionObj.options.map((option, index) => {
        return `<button onclick="checkAnswer('${option}')" key=${index}>${option}</button>`;
    }).join('<br>');

    quizContainer.innerHTML = `<div id="question"><h2>${questionObj.question}</h2>${optionsHtml}</div>`;
}

function checkAnswer(selectedOption) {
    if (questions[currentQuestionIndex].answer === selectedOption) {
        correctAnswers++;
    }
    currentQuestionIndex++;
    nextQuestion();
}

function nextQuestion() {
    if (currentQuestionIndex >= questions.length) {
        document.getElementById('quiz-container').innerHTML = `<h2>You answered ${correctAnswers} out of ${questions.length} questions correctly.</h2>`;
        return;
    }
    displayQuestion();
}

displayQuestion(); // Start the quiz immediately
