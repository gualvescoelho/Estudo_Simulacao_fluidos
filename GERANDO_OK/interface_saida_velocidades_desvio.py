import tkinter as tk
import os as op
from tkinter import messagebox

# nome_in = 1
# qtd_coord = 2
# itmin = 3
# qtd_linhas = 4

class Tela:
    def __init__(self, master):
        self.nossaTela = master

        self.vel_var_x = tk.StringVar()
        self.vel_var_y = tk.StringVar()
        self.vel_var_z = tk.StringVar()

        self.vel_geral = tk.StringVar()

        self.coordenadas_var = tk.StringVar()

        self.graf_var_x = tk.StringVar()
        self.graf_var_y = tk.StringVar()
        self.graf_var_z = tk.StringVar()

        self.dp_var_x = tk.StringVar()
        self.dp_var_y = tk.StringVar()
        self.dp_var_z = tk.StringVar()

        # criar frames
        self.nome_in = tk.Frame(self.nossaTela)
        self.qtd_coord = tk.Frame(self.nossaTela)
        self.itmin = tk.Frame(self.nossaTela)
        self.qtd_linhas = tk.Frame(self.nossaTela)
        self.velocidades = tk.Frame(self.nossaTela)
        self.coordenadas = tk.Frame(self.nossaTela)
        self.vel_graficos = tk.Frame(self.nossaTela)
        self.decisao_dp = tk.Frame(self.nossaTela)

        self.enviar = tk.Frame(self.nossaTela)

        # empacotamento
        self.nome_in.pack()
        self.qtd_coord.pack()
        self.itmin.pack()
        self.qtd_linhas.pack()
        self.velocidades.pack()
        self.coordenadas.pack()
        self.vel_graficos.pack()
        self.decisao_dp.pack()
        self.enviar.pack()

        # textos das perguntas nos frames
        self.lbl_nome_in = tk.Label(self.nome_in, text="Informe o nome do arquivo a ser lido: ")
        self.lbl_qtd_coord = tk.Label(self.qtd_coord, text="Informe a quantidade de coordenadas: ")
        self.lbl_itmin = tk.Label(self.itmin, text="Informe a quantidade de linhas que serão ignoradas: ")
        self.lbl_qtd_linhas = tk.Label(self.qtd_linhas, text="Informe a quantidade de linhas presente no arquivo: ")
        self.lbl_velocidades = tk.Label(self.velocidades, text="Informe qual velocidade deseja calcular: ")
        self.lbl_coordenadas = tk.Label(self.coordenadas, text="Informe se deseja gerar arquivo de saida com as coordenadas: ")
        self.lbl_vel_graficos = tk.Label(self.vel_graficos, text="Informe de qual velocidade deseja gerar gráfico: ")
        self.lbl_decisao_dp = tk.Label(self.decisao_dp, text="Informe se deseja calcular desvio padrão: ")

        # empacotamento dos textos e dps arrumar posicionamento
        self.lbl_nome_in.pack()
        self.lbl_qtd_coord.pack(padx = 10)
        self.lbl_itmin.pack()
        self.lbl_qtd_linhas.pack()
        self.lbl_velocidades.pack()
        self.lbl_coordenadas.pack()
        self.lbl_vel_graficos.pack()
        self.lbl_decisao_dp.pack()


        # geração da entrada de variaveis
        self.entrada_nome_in = tk.Entry(self.nome_in)
        self.entrada_qtd_coord = tk.Entry(self.qtd_coord)
        self.entrada_itmin = tk.Entry(self.itmin)
        self.entrada_qtd_linhas = tk.Entry(self.qtd_linhas)

        self.entrada_nome_in.pack()
        self.entrada_qtd_coord.pack()
        self.entrada_itmin.pack()
        self.entrada_qtd_linhas.pack()

        self.cb_vel_var_x = tk.Checkbutton(self.velocidades, text="Velocidade x: ", variable=self.vel_var_x,
                                       offvalue="0", onvalue="1")
        self.cb_vel_var_y = tk.Checkbutton(self.velocidades, text="Velocidade y: ", variable=self.vel_var_y,
                                       offvalue="0", onvalue="1")
        self.cb_vel_var_z = tk.Checkbutton(self.velocidades, text="Velocidade z: ", variable=self.vel_var_z,
                                       offvalue="0", onvalue="1")

        self.cb_vel_geral = tk.Checkbutton(self.velocidades, text="Velocidades gerais: ", variable=self.vel_geral,
                                       offvalue="0", onvalue="1")

        self.cb_coordenadas_var = tk.Checkbutton(self.coordenadas, text="Gerar coordenadas: ", variable=self.coordenadas_var,
                                       offvalue="0", onvalue="1")

        self.cb_graf_var_x = tk.Checkbutton(self.vel_graficos, text="Velocidade grafico x: ", variable=self.graf_var_x,
                                       offvalue="0", onvalue="1")
        self.cb_graf_var_y = tk.Checkbutton(self.vel_graficos, text="Velocidade grafico y: ", variable=self.graf_var_y,
                                       offvalue="0", onvalue="1")
        self.cb_graf_var_z = tk.Checkbutton(self.vel_graficos, text="Velocidade grafico z: ", variable=self.graf_var_z,
                                       offvalue="0", onvalue="1")

        self.cb_dp_var_x = tk.Checkbutton(self.decisao_dp, text="Calcular desvio padrão de x: ", variable=self.dp_var_x,
                                       offvalue="0", onvalue="1")
        self.cb_dp_var_y = tk.Checkbutton(self.decisao_dp, text="Calcular desvio padrão de y: ", variable=self.dp_var_y,
                                       offvalue="0", onvalue="2")
        self.cb_dp_var_z = tk.Checkbutton(self.decisao_dp, text="Calcular desvio padrão de z: ", variable=self.dp_var_z,
                                       offvalue="0", onvalue="3")

        self.cb_vel_var_x.pack()
        self.cb_vel_var_y.pack()
        self.cb_vel_var_z.pack()

        self.cb_vel_geral.pack()

        self.cb_coordenadas_var.pack()

        self.cb_graf_var_x.pack()
        self.cb_graf_var_y.pack()
        self.cb_graf_var_z.pack()

        self.cb_dp_var_x.pack()
        self.cb_dp_var_y.pack()
        self.cb_dp_var_z.pack()

        self.cb_vel_var_x.deselect()
        self.cb_vel_var_y.deselect()
        self.cb_vel_var_z.deselect()

        self.cb_vel_geral.deselect()

        self.cb_coordenadas_var.deselect()

        self.cb_graf_var_x.deselect()
        self.cb_graf_var_y.deselect()
        self.cb_graf_var_z.deselect()

        self.cb_dp_var_x.deselect()
        self.cb_dp_var_y.deselect()
        self.cb_dp_var_z.deselect()

        self.confirmar = tk.Button(self.enviar, text="Confirmar dados", command=self.gerar_arq_saida)
        self.confirmar.pack(side=tk.BOTTOM, pady=10)

    def gerar_arq_saida(self):
        try: #verifica se o arquivo existe
            with open(self.entrada_nome_in.get(), 'r') as f:
                f.readline()
        except IOError:
            messagebox.showinfo("Caixa de mensagem", "Erro ao procurar arquivo!\nTente novamente!")
            op.system("python interface_1_saida_vel_coord.py")
            quit()

        op.system("MKDIR vel_media")
        op.system("MKDIR coordenadas")
        op.system("MKDIR vel_media_grafico")
        op.system("MKDIR desvios_padrao")
        op.system(
            "saidas_desvio.exe " + self.entrada_nome_in.get() + " " + self.entrada_qtd_coord.get() + " " + self.entrada_itmin.get() + " " + self.entrada_qtd_linhas.get()+" "+self.vel_var_x.get()+" "+self.vel_var_y.get()+" "+self.vel_var_z.get()+" "+self.vel_geral.get()+" "+self.coordenadas_var.get()+" "+self.graf_var_x.get()+" "+self.graf_var_y.get()+" "+self.graf_var_z.get()+" "+self.dp_var_x.get()+" "+self.dp_var_y.get()+" "+self.dp_var_z.get())
        messagebox.showinfo("Caixa de mensagem", "Arquivos gerados e prontos para estudo!\nVerifique as pastas novas e renomeie os arquivos!")

janelaRaiz = tk.Tk()

Tela(janelaRaiz)

janelaRaiz.mainloop()
