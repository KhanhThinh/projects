from flask import Flask, render_template

app = Flask(__name__)


@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')


@app.route('/interactive', methods=['GET'])
def interactive():
    return render_template("academic/interactive.html")


@app.errorhandler(404)
def requestError(e):
    return render_template("errors/404.html")


@app.errorhandler(500)
@app.errorhandler(503)
def serverError(e):
    return render_template("errors/5xx.html")
