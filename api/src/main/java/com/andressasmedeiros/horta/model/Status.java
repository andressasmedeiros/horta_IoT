package com.andressasmedeiros.horta.model;

public class Status {

    private int umidadeSolo;
    private int statusLuz;
    private double temperatura;
    private int umidade;
    private boolean chuva;
    private int statusAgua;

    public int getStatusAgua() {
        return statusAgua;
    }

    public void setStatusAgua(int statusAgua) {
        this.statusAgua = statusAgua;
    }

    public boolean isChuva() {
        return chuva;
    }

    public void setChuva(boolean chuva) {
        this.chuva = chuva;
    }

    // ---------- Getters e Setters ----------
    public int getUmidadeSolo() {
        return umidadeSolo;
    }

    public void setUmidadeSolo(int umidadeSolo) {
        this.umidadeSolo = umidadeSolo;
    }

    public int getStatusLuz() {
        return statusLuz;
    }

    public void setStatusLuz(int statusLuz) {
        this.statusLuz = statusLuz;
    }

    public double getTemperatura() {
        return temperatura;
    }

    public void setTemperatura(double temperatura) {
        this.temperatura = temperatura;
    }

    public int getUmidade() {
        return umidade;
    }

    public void setUmidade(int umidade) {
        this.umidade = umidade;
    }

}
