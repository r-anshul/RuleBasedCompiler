function extractVariables(rule) {

    const keywords = [
        "IF",
        "THEN",
        "AND",
        "OR"
    ];

    const variables = new Set();

    const regex =
        /[a-zA-Z_][a-zA-Z0-9_]*/g;

    const conditionPart =
    rule.split("THEN")[0];

const matches =
    conditionPart.match(regex);

    if (!matches)
        return [];

    matches.forEach(token => {

        if (
            !keywords.includes(token) &&
            isNaN(token)
        ) {
            variables.add(token);
        }

    });

    return [...variables];
}
function generateVariableInputs() {

    let rule =
        document.getElementById("ruleInput").value;

    let variables =
        extractVariables(rule);

    let container =
        document.getElementById("variableInputs");

    container.innerHTML = "";

    variables.forEach(variable => {

        let input =
            document.createElement("input");

        input.type = "number";

        input.placeholder = variable;

        input.id = variable;

        container.appendChild(input);

    });

}  

async function runRule() {

    let rule =
        document.getElementById("ruleInput").value;

    let variableInputs =
    document.querySelectorAll(
        "#variableInputs input"
    );

let variables = {};

variableInputs.forEach(input => {

    variables[input.id] =
        Number(input.value);

});

    try {

        const response = await fetch(
            "http://localhost:3000/run",
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({
                    rule,
                    variables
                })
            }
        );

        const data = await response.json();

        document.getElementById("tokens")
            .textContent = data.tokens;

        document.getElementById("tac")
            .textContent = data.tac;

        document.getElementById("result")
            .textContent = data.result;

        document.getElementById("astTree")
            .innerHTML = "";

        const treeStructure = {
            chart: {
                container: "#astTree"
            },

            nodeStructure:
                convertToTreant(data.ast)
        };

        new Treant(treeStructure);

    }

    catch (error) {

        console.error(error);

        alert("Compilation failed");

    }

}

function convertToTreant(node) {

    if (!node)
        return {};

    let treantNode = {
        text: {
            name: node.name
        }
    };

    if (node.children &&
        node.children.length > 0)
    {
        treantNode.children =
            node.children.map(child =>
                convertToTreant(child)
            );
    }

    return treantNode;
}