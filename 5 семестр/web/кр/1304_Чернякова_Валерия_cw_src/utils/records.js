const showRecordsTable = () => {
    const yourScore = document.getElementById('endText');
    yourScore.textContent = `Ваш лучший результат: ${localStorage.getItem('ninja.score')}`;

    let scoreTable = JSON.parse(localStorage.getItem('ninja.allScores'));
    scoreTable = Object.entries(scoreTable).map(([key, value]) => [key, value])
        .sort((first, second) => {
            if (second[1] === first[1]) {
                return (first[0] < second[0]) ? -1 : 1;
            }
            return second[1] - first[1];
        });

    const scoreTableHtml = document.querySelector('.score-table');
    for (let i = 0; i < scoreTable.length; i++) {
        const line = document.createElement('h5');
        line.id = `line${i}`;
        scoreTableHtml.appendChild(line);
        if (scoreTable[i] !== undefined) {
            line.textContent = `${i + 1}. ${scoreTable[i][0]} ${scoreTable[i][1]}`;
        }
    }
};