import typer

app = typer.Typer()

@app.command()
def main(name: str):
    print(f"Hello {name}")
