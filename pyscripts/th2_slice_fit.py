import numpy as np
import ROOT


def fit_and_get_width_gr(
    h2: ROOT.TH2, x_min: float, x_max: float, delta: float, max_entry=1000
) -> ROOT.TGraph:
    gr = ROOT.TGraph()
    gaus_tf1 = ROOT.TF1("gaus_fit", "gaus(0)")
    i = 0
    for x_center in np.arange(x_min + delta / 2.0, x_max, 0.1):
        bin_min = h2.GetXaxis().FindBin(x_center - delta / 2.0)
        bin_max = h2.GetXaxis().FindBin(x_center + delta / 2.0)
        h = h2.ProjectionY(f"h_{x_center}", bin_min, bin_max)

        entries = h.GetEntries()
        if entries < max_entry:
            continue

        h.Fit(gaus_tf1, "q")

        ndf = gaus_tf1.GetNDF()
        if ndf == 0:
            continue

        chi2 = gaus_tf1.GetChisquare()
        reduced_chi2 = chi2 / ndf
        # three order
        if reduced_chi2 > 1000 or reduced_chi2 < 0.001:
            print(f"chi2 is far from 1: {reduced_chi2:.6f}")
            continue

        gr.SetPoint(i, x_center, gaus_tf1.GetParameter(2))
        i += 1
    return gr


if __name__ == "__main__":
    hist = ROOT.TH2F("h2", "h2", 100, -20.0, 20.0, 100, -20.0, 20.0)
    for i in range(100000):
        uniform = ROOT.gRandom.Uniform()
        x = 20.0 * (uniform - 0.5)
        y = ROOT.gRandom.Gaus(x, 1.0 + 0.02 * x**2)
        hist.Fill(x, y)

    do_test = True
    if do_test:
        canvas = ROOT.TCanvas("c1", "c1", 800, 800)
        canvas.SetGrid()
        canvas.Clear()
        gr = fit_and_get_width_gr(hist, -10.0, 10.0, 1.0)
        gr.SetMarkerStyle(20)
        gr.SetMarkerSize(1.0)
        gr.Draw("ap")
        canvas.Draw()
        canvas.SaveAs("c1.png")
