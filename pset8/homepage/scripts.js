document.addEventListener('DOMContentLoaded',
    () => {
        let cat = document.querySelector('.carousel-inner');
        cat.addEventListener('click',
            event => {
                alert("Don't touch the cat!!!!!");
            }
        )
        let p = document.querySelector('.lead');
        p.addEventListener('click',
            event => {
                let string = p.innerHTML
                for (let i = 0; i < string.length; i++)
                {
                    let idx = Math.floor(Math.random() * string.length);
                    string = string.replace(string[i], string[idx]);

                };
                p.innerHTML = string;
            }
        )

    }
);