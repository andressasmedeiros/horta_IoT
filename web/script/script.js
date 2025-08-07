document.addEventListener('DOMContentLoaded', () => {
    fetch('http://localhost:8080/api/status')
        .then(res => res.json())
        .then(dados => {
            console.log("Dados recebidos da API:", dados); // <-- debug
            renderCards(dados);
        })
        .catch(err => console.error('Erro ao buscar dados da API:', err));

    const aboutBtn = document.getElementById('aboutBtn');
    const modal = document.getElementById('aboutModal');
    const closeBtn = document.getElementById('modalClose');

    // abrir
    aboutBtn.addEventListener('click', () => {
        modal.classList.add('show');
    });

    // fechar clicando no “×”
    closeBtn.addEventListener('click', () => {
        modal.classList.remove('show');
    });

    // fechar clicando fora da caixa de conteúdo
    modal.addEventListener('click', e => {
        if (e.target === modal) {
            modal.classList.remove('show');
        }
    });
});

function carregarCuriosidade() {
    fetch('data/curiosidade_horta.json')
        .then(res => res.json())
        .then(lista => {
            // Escolhe uma curiosidade aleatória
            const randomIndex = Math.floor(Math.random() * lista.length);
            const curiosidade = lista[randomIndex];

            // Encontra o card de curiosidade (último card da lista)
            const cardCuriosidade = document.querySelector(".cards-container .card:last-child");
            if (cardCuriosidade) {
                const imgDiv = cardCuriosidade.querySelector(".card-image");
                imgDiv.style.backgroundImage = `url('${curiosidade.imagem}')`;

                const h3 = cardCuriosidade.querySelector("h3");
                h3.textContent = "Curiosidade:";

                let p = cardCuriosidade.querySelector("p");
                if (!p) {
                    p = document.createElement("p");
                    cardCuriosidade.querySelector(".card-content").appendChild(p);
                }
                p.textContent = curiosidade.texto;
            }
        })
        .catch(err => console.error("Erro ao carregar curiosidades:", err));
}

function renderCards(dados) {
    const container = document.querySelector('.cards-container');
    container.innerHTML = ''; // limpa cards antigos

    const imgMap = {
        temperatura: dados.chuva == 1
            ? 'assets/img/temperatura.jpg'
            : 'assets/img/ensolarado.jpg',
        umidadeAr: 'assets/img/umidade-ar.jpg',
        umidadeSolo: dados.umidadeSolo >= 40
            ? 'assets/img/umidade-solo.png'
            : 'assets/img/solo-seco.jpg',
        regar: dados.statusAgua == 0
        ? 'assets/img/precisa-regar.jpg'
            : (dados.statusAgua == 1
            ? 'assets/img/regador.jpg'
            : 'assets/img/encharcado.jpg'),
        luz: dados.statusLuz == 0
            ? 'assets/img/escuro.jpg'
            : (dados.statusLuz == 1
                ? 'assets/img/pouca-luz.webp'
                : 'assets/img/muita-luz.jpg'),
        curiosidade: 'assets/img/imagem-curiosidade.jpg'
    };

    const items = [
        {
            key: 'temperatura',
            label: 'Temperatura',
            valor: `${dados.temperatura}ºC`,
            subtitle: dados.chuva == 1 ? 'Está chovendo' : 'Sem chuva'
        },
        {
            key: 'umidadeAr',
            label: 'Umidade do ar',
            valor: `${dados.umidade}%`,
            subtitle: dados.umidade < 40 ? 'Baixa' : 'Boa'
        },
        {
            key: 'umidadeSolo',
            label: 'Umidade do solo',
            valor: `${dados.umidadeSolo}%`
        },
        {
            key: 'regar',
            label: 'Solo',
            valor: dados.statusAgua == 0
                ? 'Seco'
                : (dados.statusAgua == 1
                    ? 'Bom'
                    : 'Encharcado'),
            subtitle: dados.statusAgua == 0
                ? 'Precisa Regar'
                : (dados.statusAgua == 1
                    ? 'Umidade adequada'
                    : 'Não precisa regar')
        },
        {
            key: 'luz',
            label: 'Luz ambiente',
            valor: dados.statusLuz == 0 ? 'Escuro' : (dados.statusLuz == 1 ? 'Pouca luz' : 'Muita luz'),
        },
        {
            key: 'curiosidade',
            label: 'Curiosidade',
            valor: '',
            subtitle: '' // será substituído dinamicamente
        }
    ];

    items.forEach(item => {
        const card = document.createElement('div');
        card.classList.add('card');

        const imgDiv = document.createElement('div');
        imgDiv.classList.add('card-image');
        imgDiv.style.backgroundImage = `url('${imgMap[item.key]}')`;
        card.appendChild(imgDiv);

        const content = document.createElement('div');
        content.classList.add('card-content');

        const h3 = document.createElement('h3');
        h3.textContent = `${item.label}: ${item.valor}`;
        content.appendChild(h3);

        if (item.subtitle) {
            const p2 = document.createElement('p');
            p2.textContent = item.subtitle;
            content.appendChild(p2);
        }

        card.appendChild(content);
        container.appendChild(card);
    });
    carregarCuriosidade();
}
