const fadeTextIn = (element) => {
    const paragraphs = element.getElementsByTagName('p');
    for (let i = 0; i < paragraphs.length; i++) {
        const paragraph = paragraphs[i];
        const text = paragraph.innerText;
        paragraph.innerHTML = '';
        for (let j = 0; j < text.length; j++) {
            const span = document.createElement('span');
            span.innerText = text.charAt(j);
            span.classList.add('fade-in');
            paragraph.appendChild(span);
        }
    }
    const spanArray = Array.from(element.getElementsByTagName('span'));
    const lastSpan = spanArray[spanArray.length - 1];
    lastSpan.addEventListener('transitionend', () => {
        setTimeout(() => {
            window.location.href = '../level1.html';
        }, 1000);
    });
    spanArray.forEach((span, index) => {
        setTimeout(() => { span.style.opacity = '1'; }, index * 35);
    });
};

const textContainer = document.getElementById('text-container');
fadeTextIn(textContainer);

document.addEventListener('keydown', (event) => {
    if (event.keyCode === 32) {
        const spans = document.querySelectorAll('.fade-in');
        spans.forEach(span => {
            span.style.opacity = '1';
        });
    }
});
