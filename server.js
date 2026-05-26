const express = require("express");
const cors = require("cors");
const fs = require("fs");
const { exec } = require("child_process");

const app = express();

app.use(cors());
app.use(express.json());

app.post("/run", (req, res) => {

    const rule = req.body.rule;

    const variables = req.body.variables;

    fs.writeFileSync(
        "./Back/input.txt",
        rule
    );

    fs.writeFileSync(
        "./Back/variables.json",
        JSON.stringify(variables)
    );

    exec(
        "cd Back && ./final < input.txt",

        (error, stdout, stderr) => {

            if (error) {

                return res.status(500).json({
                    error: stderr
                });

            }

            try {

                const tokens =
                    fs.readFileSync(
                        "./output/tokens.txt",
                        "utf8"
                    );

                const tac =
                    fs.readFileSync(
                        "./output/tac.txt",
                        "utf8"
                    );

                const result =
                    fs.readFileSync(
                        "./output/result.txt",
                        "utf8"
                    );

                const ast =
                    JSON.parse(
                        fs.readFileSync(
                            "./output/ast.json",
                            "utf8"
                        )
                    );

                res.json({
                    tokens,
                    tac,
                    result,
                    ast
                });

            }

            catch (err) {

                res.status(500).json({
                    error:
                    "Failed to read output files"
                });

            }

        }

    );

});

app.listen(3000, () => {
    console.log("Server running on port 3000");
});