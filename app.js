let btn = document.querySelector('#new-quote');
let quote = document.querySelector('.quote');
let person = document.querySelector('.person');

const quotes = [
    // give some quotes
    {
        quote: "The greatest glory in living lies not in never falling, but in rising every time we fall.",
        person: "Nelson Mandela"
    },
    {
        quote: "The way to get started is to quit talking and begin doing.",
        person: "Walt Disney"
    },
    {
        quote: "If life were predictable it would cease to be life, and be without flavor.",
        person: "Eleanor Roosevelt"
    },
    {
        quote: "Life is what happens when you're busy making other plans.",
        person: "John Lennon"
    },
    {
        quote: "The best and most beautiful things in the world cannot be seen or even touched - they must be felt with the heart.",
        person: "Helen Keller"
    },
    {
        quote: "It is during our darkest moments that we must focus to see the light.",
        person: "Aristotle"
    }
];

btn.addEventListener('click', function() {
    let random = Math.floor(Math.random() * quotes.length);
    quote.innerHTML = quotes[random].quote;
    person.innerHTML = quotes[random].person;
});